#include "adduserwgt.h"
#include "ui_adduserwgt.h"
#include "../DataCore/hbdatacore.h"
#include <QLineEdit>
#include <QDebug>

using namespace HBDataCore;

AddUserWgt::AddUserWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddUserWgt)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);


    createUserTable();

}

AddUserWgt::~AddUserWgt()
{
    delete ui;
}


void AddUserWgt::on_pBtn_confirm_clicked()
{
    if (ui->name_lineEdit->text().isEmpty() || ui->num_lineEdit->text().isEmpty())
    {
        qDebug() << "不能为空";
        return;
    }

    insertUser(ui->name_lineEdit->text(), ui->num_lineEdit->text());

    close();
}

void AddUserWgt::on_pBtn_cancel_clicked()
{
    close();
}
