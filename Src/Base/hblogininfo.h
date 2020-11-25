#ifndef HBLOGININFO_H
#define HBLOGININFO_H

#include <QMap>
#include <QObject>

class HBLoginInfo : public QObject
{
    Q_OBJECT
public:

    static HBLoginInfo *shareInstance();

    QString phone;
    QString token;
    QString thirdToken;

    QMap<QString, QString> jwtokenMap;


private:
    explicit HBLoginInfo(QObject *parent = nullptr);

    static HBLoginInfo *m_instance;
};

HBLoginInfo *HBLoginUser();

#endif // HBLOGININFO_H
