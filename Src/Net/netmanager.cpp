#include "netmanager.h"

#include <QNetworkAccessManager>
#include <QMutex>

#include "../Base/base.h"
#include "../Base/hblogininfo.h"

using namespace Base;

NetManager* NetManager::m_instance = nullptr;
static QMutex k_net_mutex;

NetManager *NetManager::shareInstance()
{
    if (m_instance == nullptr)
    {
        QMutexLocker locker(&k_net_mutex);
        if (m_instance == nullptr)
            m_instance = new NetManager;
    }
    return m_instance;
}

NetManager::NetManager(QObject *parent)
    : QObject(parent)
{
}

void NetManager::http(const NetManager::HttpType type, const QString urlStr, const QVariantMap param, const QString deviceId)
{

    QNetworkRequest request;
    if (type == FORM)
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/x-www-form-urlencoded"));
    else
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json;charset=utf-8"));

    QVariantMap headersMap = m_getRequestHeader(deviceId);
    foreach(QString key, headersMap.keys())
    {
        QVariant value = headersMap[key];
        QByteArray headName = key.toLocal8Bit();
        QByteArray headValue = value.toString().toLocal8Bit();
        request.setRawHeader(headName, headValue);
    }


    //QVariantMap bodyMap = hyEncryptWithUrl(urlStr, param, type == POST);
    QString m_body;





}

NetManager::~NetManager()
{

}

NetManager *NetInset()
{
    return NetManager::shareInstance();
}



QVariantMap NetManager::m_getRequestHeader(QString deviceId /* = nullptr */)
{
    QVariantMap header;

    if (!HBLoginUser()->token.isEmpty())
    {
        header["AuthorizationToken"] = HBLoginUser()->token;
    }

    header["AppName"] = appName();
    header["DeviceId"] = computerId();
    header["Version"] = appVersion();
    header["DeviceType"] = "PC";

    if (!deviceId.isEmpty())
        header["AuthorizationJwtoken"] = HBLoginUser()->jwtokenMap[deviceId];
    return header;
}


//QVariantMap HYNetManager::hyEncryptWithUrl(QString urlStr, QVariantMap param, bool paramIsBody)
//{
//	QVariantMap tempResult;	//用于加密
//	QVariantMap result;	//用于返回 url 后拼接的字段

//	auto time = QDateTime::currentMSecsSinceEpoch();
//	uint32_t nonce = QRandomGenerator::global()->bounded(10000, 99999);
//	result.insert("time", QString::number(time));
//	result.insert("nonce", QString::number(nonce));
//	tempResult.insert("time", QString::number(time));
//	tempResult.insert("nonce", QString::number(nonce));

//	for (int i = 0; i < param.keys().count(); i++)
//	{
//		QString key = param.keys()[i];
//		QVariant value = param[key];
//		if (!paramIsBody)
//		{
//			tempResult.insert(key, value);
//		}
//		result.insert(key, value);
//	}

//	if (paramIsBody)
//	{
//		QJsonDocument doc = QJsonDocument::fromVariant(QVariant(param));
//		QString str = doc.toJson(QJsonDocument::Compact);
//		tempResult.insert("content", str);
//	}


//	QStringList list;

//	for each (QString key in tempResult.keys())
//	{
//		QString value = tempResult[key].toString();
//		QString tempStr = QString("%1%2").arg(key).arg(value);
//		list << tempStr;
//	}

//	std::sort(list.begin(), list.end());

//	QString forSignStr = list.join("");
//	forSignStr.append(QUrl(urlStr).path());
//	forSignStr.append(appSecretKey());

//	auto s = MD5::MD5(forSignStr.toStdString()).toString();
//	QString sign = QString::fromStdString(s);

//	//QString sign = HYTools::MD5(forSignStr);
//	result.insert("sign", sign);

//	return result;
//}



