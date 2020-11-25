#ifndef HBDATABASE_H
#define HBDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariantMap>


class HBDatabase : public QObject
{
    Q_OBJECT
public:

    static HBDatabase *shareInstance();

    //封装的两个方法
    bool executeUpdate(const QString cmdStr);
    void executeQuery(const QString cmdStr, std::function<void(QSqlQuery query, QString errorMsg)> callback);

private:
    QSqlDatabase *m_db;
    explicit HBDatabase(QObject *parent = nullptr);

    static HBDatabase *m_instance;

};

HBDatabase *HBDBShare();

#endif // HBDATABASE_H
