#ifndef NETTOOLS_H
#define NETTOOLS_H

#include <QObject>

namespace NetTools {

enum HttpType {
    GET,POST,FORM
};

enum HttpPath {
    Login,
    LoginByThird
};

QString urlStr(const HttpPath path);

QString encryUrl(const QString urlStr, const QVariantMap param, HttpType type, QByteArray& bodyData);


} // namespace NetTools



#endif // NETTOOLS_H
