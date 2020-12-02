#ifndef ZOOMCONTROL_H
#define ZOOMCONTROL_H

#include <QWidget>
#include "colorbutton.h"

class ZoomControl : public QWidget
{
    Q_OBJECT
public:
    explicit ZoomControl(QWidget *parent = nullptr);

signals:

public slots:



private:
    ColorButton *closeBtn;
    ColorButton *minBtn;
    ColorButton *maxBtn;

};

#endif // ZOOMCONTROL_H
