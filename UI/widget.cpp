#include "widget.h"
#include "ui_widget.h"
#include "../DB/hbdatabase.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    HBDBShare()->executeUpdate("create table if not exists OrderList (user text, orderNum text, date text, goods text)");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{

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
    HBDBShare()->executeQuery("select * from Home", [&](QSqlQuery query, QString msg) {

        if (msg.isEmpty())
        {
            qDebug() << query.value("name") << "  " << query.value("person");
            log(query.value("name").toString());
            log(query.value("person").toString());
        }
        else {
            qDebug() << "Error: " << msg;
        }

    });
}


void Widget::log(const QString msg)
{
    qDebug() << "msg: " << msg;
}
