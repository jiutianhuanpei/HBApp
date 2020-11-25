#include "widget.h"
#include "ui_widget.h"
#include "../DB/hbdatabase.h"
#include <QDebug>
#include "adduserwgt.h"
#include <QGuiApplication>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);





}

Widget::~Widget()
{
    delete ui;
}


void Widget::log(const QString msg)
{
    qDebug() << "msg: " << msg;
}

void Widget::on_pBtn_add_clicked()
{
    AddUserWgt *add = new AddUserWgt();

    QRect rect = qApp->activeWindow()->geometry();

    int x = rect.x();
    int y = rect.y();

    x += ((rect.width() - add->width()) / 2.0);
    y += ((rect.height() - add->height()) / 2.0);

    add->move(x, y);
    add->show();
}

void Widget::on_pBtn_delete_clicked()
{

}

void Widget::on_pBtn_modify_clicked()
{
    ui->treeView->sortByColumn(0, Qt::AscendingOrder);
}

void Widget::on_pBtn_log_clicked()
{

    ui->treeView->sortByColumn(0, Qt::DescendingOrder);

}
