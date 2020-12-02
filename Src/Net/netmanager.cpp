#include "netmanager.h"

#include <QNetworkAccessManager>
#include <QMutex>

#include "../Base/base.h"
#include "../Base/hblogininfo.h"

#include <QEventLoop>
#include <QNetworkReply>
#include <QTimer>

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

void NetManager::http(const HttpType type, const QString urlStr, const QVariantMap param, const QString deviceId)
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

    QByteArray m_body;

    QString url = encryUrl(urlStr, param, type, m_body);

    request.setUrl(QUrl(url));

    QNetworkAccessManager manager;

    QNetworkReply *reply;

    if (type == GET)
    {
        reply = manager.get(request);
        manager.setParent(reply);
    }
    else {
        reply = manager.post(request, m_body);
        manager.setParent(reply);
    }


    QEventLoop loop;
    QTimer timer;

    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);


    timer.start(10000);
    loop.exec();

    QNetworkReply::NetworkError error = reply->error();

    if (error != QNetworkReply::NoError)
    {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray response = reply->readAll();
    reply->deleteLater();


    qDebug() << "Response:" << response;



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


