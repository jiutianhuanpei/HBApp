#ifndef BASE_H
#define BASE_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariantMap>


namespace Base {

QString appSecretKey();
QString appName();
QString appVersion();
QString computerId();

QString uuid();

int randomNumber();

QString MD5(const QString str);


qint64 getLongData(const QJsonObject& json, const QString key);


double getDouble(const QJsonObject& json, const QString key);
int getInt(const QJsonObject& json, const QString key);
QString getString(const QJsonObject& json, const QString key);
bool getBool(const QJsonObject& json, const QString key);
QJsonArray getArray(const QJsonObject& json, const QString key);
QJsonObject getObject(const QJsonObject& json, const QString key);

QString stringFromJson(const QJsonObject& json, QJsonDocument::JsonFormat format = QJsonDocument::Compact);
QJsonObject jsonFromStr(const QString jsonStr);

QByteArray stringFromMap(const QVariantMap& map, QJsonDocument::JsonFormat format = QJsonDocument::Compact);





} // namespace Base

#endif // BASE_H
