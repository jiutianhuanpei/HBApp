#include "messagecore.h"
#include <QMutex>

MessageCore *MessageCore::m_instance = nullptr;


static QMutex k_msg_mutex;


MessageCore *MessageCore::shareInstance()
{
    if (m_instance == nullptr)
    {
        QMutexLocker locker(&k_msg_mutex);
        if (m_instance == nullptr)
            m_instance = new MessageCore;
    }
    return m_instance;
}

MessageCore::MessageCore(QObject *parent) : QObject(parent)
{

}

MessageCore *MsgInset()
{
    return MessageCore::shareInstance();
}
