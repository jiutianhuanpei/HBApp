#include "hblogininfo.h"
#include <QMutex>


HBLoginInfo *HBLoginInfo::m_instance = nullptr;
static QMutex k_user_mutex;


HBLoginInfo *HBLoginInfo::shareInstance()
{
    if (m_instance == nullptr)
    {
        QMutexLocker locker(&k_user_mutex);
        if (m_instance == nullptr)
            m_instance = new HBLoginInfo;
    }
    return m_instance;
}

HBLoginInfo::HBLoginInfo(QObject *parent) : QObject(parent)
{

}

HBLoginInfo *HBLoginUser()
{
    return HBLoginInfo::shareInstance();
}
