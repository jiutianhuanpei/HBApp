#include "colorbutton.h"

ColorButton::ColorButton(QWidget *parent) : QWidget(parent)
{



}

void ColorButton::setType(ColorButton::ButtonType type)
{
    QString colorStr;
    if (type == Close)
        colorStr = "red";
    else if (type == Min)
        colorStr = "yellow";
    else
        colorStr = "green";

    QString style = QString("background: %1;").arg(colorStr);
    setStyleSheet(style);
}

void ColorButton::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    emit signalDidClickedBtn();
}
