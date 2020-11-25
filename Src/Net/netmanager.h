#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <QObject>

class NetManager : public QObject
{

    Q_OBJECT

public:
    static NetManager *shareInstance();
    NetManager(QObject *parent = nullptr);

    enum HttpType {
        GET,POST,FORM
    };


    void http(const HttpType type, const QString url, const QVariantMap param, const QString deviceId);


private:
    ~NetManager();

    static NetManager *m_instance;

private:
    QVariantMap m_getRequestHeader(QString deviceId = nullptr);

};

NetManager *NetInset();



#endif // NETMANAGER_H
