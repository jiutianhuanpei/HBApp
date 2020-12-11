#include "hbwebimagemanager.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>
#include <QHostInfo>
#include <QDebug>
#include <QDir>
#include <QCryptographicHash>
#include <QDataStream>
#include <QBuffer>

HBWebImageManager::HBWebImageManager(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QPixmap>("QPixmap");
}

void HBWebImageManager::fetchImage(const QString urlStr)
{

    QString name = cacheName(urlStr);
    QString path = QString("%1/%2").arg(QDir::tempPath()).arg(name);
    QFile cacheFile(path);
    if (cacheFile.exists())
    {
        qDebug() << "Path: " << path;

        QPixmap pix;
        pix.load(path);
        qDebug() << "Pix: " << pix.width() << pix.height();
        emit signal_getImage(pix);
        return;
    }

    m_urlStr = urlStr;
    //构造请求
    QNetworkRequest request;
    request.setUrl(QUrl(m_urlStr));
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    // 发送请求
    QNetworkReply *pReplay = manager->get(request);
    //开启一个局部的事件循环，等待响应结束，退出
    QEventLoop eventLoop;
    QObject::connect(pReplay,SIGNAL(finished()), &eventLoop, SLOT(quit()));

    //add timeout deal
    QTimer *tmpTimer = new QTimer();
    connect(tmpTimer,SIGNAL(timeout()),&eventLoop, SLOT(quit()));
    tmpTimer->setSingleShot(true);
    tmpTimer->start(5000);
    eventLoop.exec();
    tmpTimer->stop();

    if (pReplay->error() == QNetworkReply::NoError)
    {
        QByteArray array = pReplay->readAll();

        qDebug() << "Length: " << array.length();

        QPixmap pix;
        pix.loadFromData(array);

        qDebug() << "Pix: " << pix.width() << pix.height();
        emit signal_getImage(pix);
        cacheImage(m_urlStr, array);
    }
    else
    {
        qWarning()<<QString("request %1 handle errors here");//.arg(obj);
        QVariant statusCodeV = pReplay->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        //statusCodeV是HTTP服务器的相应码，reply->error()是Qt定义的错误码，可以参考QT的文档
        qWarning()<<QString("request %1 found error ....code: %2 ").arg(statusCodeV.toInt()).arg((int)pReplay->error());
        qWarning(qPrintable(pReplay->errorString()));
    }

    pReplay->deleteLater();
    manager->deleteLater();
}

void HBWebImageManager::cacheImage(const QString urlStr, const QByteArray tempByte)
{

    QString name = cacheName(urlStr);

    qDebug() << "\nURL: " << urlStr << "\nBase: " << name;

    QString path = QString("%1/%2").arg(QDir::tempPath()).arg(name);

    QPixmap pix(path);
    QByteArray bytes = tempByte;
    QBuffer buffer(&bytes);

    buffer.open(QIODevice::WriteOnly);
    pix.save(&buffer);
}

QString HBWebImageManager::cacheName(const QString urlStr)
{
    QByteArray array = QCryptographicHash::hash(urlStr.toUtf8(), QCryptographicHash::Sha256);
    QString name = array.toHex();
    return name;
}

