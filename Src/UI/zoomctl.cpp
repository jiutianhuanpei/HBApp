#include "zoomctl.h"
#include "ui_zoomctl.h"
#include <QPushButton>

ZoomCtl::ZoomCtl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZoomCtl)
{
    ui->setupUi(this);

    qRegisterMetaType<WindowZoom>("WindowZoom");

    connect(ui->pBtn_Close, &QPushButton::clicked, [&] {
       emit signal_didClicked(Close);
    });
    connect(ui->pBtn_Min, &QPushButton::clicked, [&] {
       emit signal_didClicked(Min);
    });
    connect(ui->pBtn_Max, &QPushButton::clicked, [&] {
       emit signal_didClicked(Max);
    });

}

ZoomCtl::~ZoomCtl()
{
    delete ui;
}
