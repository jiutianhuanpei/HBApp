#ifndef HBDATACORE_H
#define HBDATACORE_H

#include <QObject>

//class HBDataCore : public QObject
//{
//    Q_OBJECT
//public:
//    explicit HBDataCore(QObject *parent = nullptr);

//};

namespace HBDataCore {
void createUserTable();
void insertUser(const QString name, const QString orderNum);


} // namespace HBDataCore



#endif // HBDATACORE_H
