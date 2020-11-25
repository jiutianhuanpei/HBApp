#include "hbdatabase.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMutex>
#include <QMutexLocker>

HBDatabase *HBDBShare()
{
    return HBDatabase::shareInstance();
}

HBDatabase * HBDatabase::m_instance = nullptr;
static QMutex k_data_mutex;
HBDatabase *HBDatabase::shareInstance()
{
    if (m_instance == nullptr)
    {
        QMutexLocker locker(&k_data_mutex);
        if (m_instance == nullptr)
            m_instance = new HBDatabase;
    }
    return m_instance;
}

HBDatabase::HBDatabase(QObject *parent) : QObject(parent)
{

    //QMutexLocker locker(&k_data_mutex);
    m_db = new QSqlDatabase;

    *m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db->setDatabaseName("HBApp.db");
    m_db->setUserName("Bang");
    m_db->setPassword("1234");
}


bool HBDatabase::executeUpdate(const QString cmdStr)
{
    bool isOK = false;

    if (!m_db->open())
        return isOK;

    QSqlQuery query(*m_db);

    query.prepare(cmdStr);

    isOK = query.exec();

    if (!isOK)
        qDebug() << "executeUpdate failure: " << query.lastError();

    m_db->close();
    return isOK;
}

void HBDatabase::executeQuery(const QString cmdStr, std::function<void (QSqlQuery, QString)> callback)
{

    bool isOk = false;
    if (!m_db->open())
        return;

    QSqlQuery query(*m_db);

    query.prepare(cmdStr);

    isOk = query.exec();

    if (!isOk)
    {
        qDebug() << "executeQuery failure: " << query.lastError();
        if (callback != NULL)
            callback(query, query.lastError().text());
        m_db->close();
        return;
    }

    if (callback != NULL)
    {
        while (query.next()) {
           callback(query, "");
        }
    }

    m_db->close();
}

