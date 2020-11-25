#include "base.h"
#include <QUuid>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QCryptographicHash>
#include <QJsonValue>
#include <QJsonArray>

namespace Base {

QString appName()
{
    return "anfangadmin";
}

QString appVersion()
{
    return "1.1000.5.40";
}

QString uuid()
{
    QUuid uid = QUuid::createUuid();
    QString str = uid.toString(QUuid::Id128);
    return str;
}

QString computerId()
{
    QString computerIdPath(".computerId");

    QFile file(computerIdPath);
    if (file.exists())
    {
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QString aid = file.readAll();
        if (aid.isEmpty())
        {
            aid = uuid();
            QTextStream stream(&file);
            stream << aid;
            file.close();
            return aid;
        }
        file.close();
        return aid;
    }

    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QString aId = uuid();
    QTextStream stream(&file);
    stream << aId;
    file.close();
    return aId;
}

int randomNumber()
{
    int num = QRandomGenerator::global()->bounded(10000, 99999);
    return num;
}

QString MD5(const QString str)
{
    QByteArray byte = QCryptographicHash::hash(str.toStdString().c_str(), QCryptographicHash::Md5);

    QString result = byte.toHex();
    return result;
}

QString appSecretKey()
{
    return "r8rw4d1kjwqgqqto9dwsq3ew0ip2np1b";
}


qint64 getLongData(const QJsonObject& json, const QString key)
{

    QJsonValue value = json.value(key);

    double num = 0;
    if (value.isDouble())
    {
        num = value.toDouble();
    }
    else if (value.isString())
    {
        num = json.value(key).toString().toDouble();
    }

    return QString::number(num, 'f', 0).toLongLong();
}

double getDouble(const QJsonObject& json, const QString key)
{
    QJsonValue value = json.value(key);

    double num = 0;
    if (value.isDouble())
    {
        num = value.toDouble();
    }
    else if (value.isString())
    {
        num = json.value(key).toString().toDouble();
    }

    return num;
}

int getInt(const QJsonObject& json, const QString key)
{
    QJsonValue value = json.value(key);
    if (value.isString())
        return value.toString().toInt();

    if (value.isDouble())
        return value.toInt();

    return 0;
}

QString getString(const QJsonObject& json, const QString key)
{
    return json.value(key).toString("");
}

bool getBool(const QJsonObject& json, const QString key)
{
    QJsonValue value = json.value(key);
    if (value.isBool())
        return value.toBool(false);

    if (value.isDouble())
    {
        int a = value.toInt();
        return a != 0;
    }

    if (value.isString())
    {
        QString s = value.toString();
        if (s == "0") return false;
        if (s == "true") return true;
        if (s == "TRUE") return true;
        if (s == "FALSE") return false;
    }

    return json.value(key).toBool(false);
}

QJsonObject getObject(const QJsonObject& json, const QString key)
{
    return json.value(key).toObject();
}

QJsonArray getArray(const QJsonObject& json, const QString key)
{
    return json.value(key).toArray();
}


QString stringFromJson(const QJsonObject& json, QJsonDocument::JsonFormat format /* = QJsonDocument::Compact */)
{
    QJsonDocument doc(json);
    return doc.toJson(format);
}

QJsonObject jsonFromStr(const QString jsonStr)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toStdString().c_str());
    return doc.object();
}

QByteArray stringFromMap(const QVariantMap& map, QJsonDocument::JsonFormat format /* = QJsonDocument::Compact */)
{
    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(map));
    return doc.toJson(format);
}





} // namespace Base
