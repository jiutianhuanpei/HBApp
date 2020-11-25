#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <QObject>

class NetManager : public QObject
{

    Q_OBJECT

public:
    static NetManager *shareInstance();
    NetManager(QObject *parent = nullptr);



private:
    ~NetManager();

    static NetManager *m_instance;

};

NetManager *NetInset();



#endif // NETMANAGER_H
