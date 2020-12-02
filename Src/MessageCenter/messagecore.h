#ifndef MESSAGECORE_H
#define MESSAGECORE_H

#include <QObject>
#include "../Src/UI/uiheader.h"


class MessageCore : public QObject
{
    Q_OBJECT
public:
    static MessageCore *shareInstance();

signals:
    void signal_windowZoom(WindowZoom zoom);



private:
    explicit MessageCore(QObject *parent = nullptr);

    static MessageCore *m_instance;
};

MessageCore * MsgInset();

#endif // MESSAGECORE_H
