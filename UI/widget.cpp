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

void Widget::on_pushButton_clicked()
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

void Widget::on_pushButton_2_clicked()
{
   // m_database->createTable("Home", QStringList() << "name text" << "person Integer");
}

void Widget::on_pushButton_3_clicked()
{
    //m_database->executeUpdate("insert into Home (name, person) values ('Bang', 20)");
}

void Widget::on_pushButton_4_clicked()
{

    ui->treeView->setData();
}


void Widget::log(const QString msg)
{
    qDebug() << "msg: " << msg;
}
