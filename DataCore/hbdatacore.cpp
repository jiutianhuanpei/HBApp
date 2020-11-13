#include "hbdatacore.h"
#include "../DB/hbdatabase.h"

//HBDataCore::HBDataCore(QObject *parent) : QObject(parent)
//{

//}


namespace HBDataCore {

void createUserTable()
{

    QString cmdStr = "create table if not exists User (name text primary key, orderNum text not null, goods text)";

    HBDBShare()->executeUpdate(cmdStr);
}

void insertUser(const QString name, const QString orderNum)
{
    QString cmdStr = QString("insert into User (name, orderNum) values ('%1', '%2')").arg(name, orderNum);
    HBDBShare()->executeUpdate(cmdStr);
}

} // namespace HBDataCore
