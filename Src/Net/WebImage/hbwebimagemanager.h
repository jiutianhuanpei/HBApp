#ifndef HBWEBIMAGEMANAGER_H
#define HBWEBIMAGEMANAGER_H

#include <QFile>
#include <QObject>
#include <QPixmap>
#include <QTcpSocket>
#include <QLabel>

class HBWebImageManager : public QObject
{
    Q_OBJECT
public:
    explicit HBWebImageManager(QObject *parent = nullptr);

signals:
    void signal_getImage(const QPixmap & image);


public slots:
    void fetchImage(const QString urlStr);

private:

    QString m_urlStr;

    void cacheImage(const QString urlStr, const QByteArray byte);


    QString cacheName(const QString urlStr);

};

#endif // HBWEBIMAGEMANAGER_H
