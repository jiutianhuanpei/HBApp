#include "colorbutton.h"

ColorButton::ColorButton(ButtonType type, QWidget *parent) : QWidget(parent)
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

void ColorButton::mousePressEvent(QMouseEvent event)
{
    QWidget::mousePressEvent(event);
    emit signalDidClickedBtn();
}
