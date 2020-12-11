#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <QObject>
#include <QVariantMap>
#include "nettools.h"

using namespace NetTools;

class NetManager : public QObject
{

    Q_OBJECT

public:
    static NetManager *shareInstance();
    NetManager(QObject *parent = nullptr);




    void http(const HttpType type, const QString url, const QVariantMap param = QVariantMap(), const QString deviceId = "");


private:
    ~NetManager();

    static NetManager *m_instance;

private:
    QVariantMap m_getRequestHeader(QString deviceId = nullptr);

};

NetManager *NetInset();



#endif // NETMANAGER_H
