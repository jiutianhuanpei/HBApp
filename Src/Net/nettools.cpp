#include "nettools.h"
#include "../Base/base.h"
#include <QDateTime>
#include <QUrl>

using namespace Base;

namespace NetTools {

QMap<HttpPath, QString> pathMap()
{
    QMap<HttpPath, QString> map;
//    map.insert(Login, "user/admin/login/userAuthBySms");
   map[Login] = "user/admin/login/userAuthBySms";
   map[LoginByThird] = "user/login/loginByThird";


    return map;
}



QString queryPath(const QVariantMap param)
{
    QStringList list;

    foreach (QString key, param.keys()) {
        QString str = QString("%1=%2").arg(key).arg(param[key].toString());
        list << str;
    }

    return list.join("&");
}


QString encryUrl(const QString urlStr, const QVariantMap param, HttpType type, QByteArray &bodyData)
{
    qint64 time = QDateTime::currentDateTime().toMSecsSinceEpoch();
    int nonce = randomNumber();

    QVariantMap forSignMap;
    forSignMap["time"] = time;
    forSignMap["nonce"] = nonce;

    if (type == POST)
    {
        QString str = stringFromMap(param);
        forSignMap["content"] = str;
    }
    else
    {
        foreach (QString key, param.keys()) {
            forSignMap[key] = param[key];
        }
    }

    QStringList strList;

    foreach (QString key, forSignMap.keys()) {

        QString str = QString("%1%2").arg(key).arg(forSignMap[key].toString());
        strList << str;
    }

    std::sort(strList.begin(), strList.end());

    QString forSignStr = strList.join("");
    forSignStr = forSignStr.append(QUrl(urlStr).path());
    forSignStr = forSignStr.append(appSecretKey());

    QString sign = MD5(forSignStr);

    forSignMap.remove("content");

    forSignMap["sign"] = sign;


    QString url;

    if (type == GET)
    {

        foreach (QString key, param.keys()) {
            forSignMap[key] = param[key];
        }

        url = QString("%1?%2").arg(urlStr).arg(queryPath(forSignMap));
        bodyData = nullptr;
    }
    else if (type == POST) {

        url = QString("%1?%2").arg(urlStr).arg(queryPath(forSignMap));
        bodyData = stringFromMap(param);
    }
    else {
        url = QString("%1?%2").arg(urlStr).arg(queryPath(forSignMap));
        bodyData = queryPath(param).toStdString().c_str();
    }

    return url;
}

QString urlStr(const HttpPath path)
{
    QString pathStr = pathMap()[path];

    return QString("%1%2").arg("http://hy-dj-api.worthcloud.net:9001/").arg(pathStr);
}

} // namespace NetTools
