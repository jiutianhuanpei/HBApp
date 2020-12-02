#include "zoomcontrol.h"
#include <QHBoxLayout>

ZoomControl::ZoomControl(QWidget *parent) : QWidget(parent)
{

    closeBtn = new ColorButton(ColorButton::Close, this);
    minBtn = new ColorButton(ColorButton::Min);
    maxBtn = new ColorButton(ColorButton::Max);


//    QHBoxLayout *layout = new QHBoxLayout(this);
//    layout->setContentsMargins(0, 0, 0, 0);
//    layout->addWidget(closeBtn);
//    layout->addWidget(minBtn);
//    layout->addWidget(maxBtn);

//    setFixedSize(100, 30);

}
