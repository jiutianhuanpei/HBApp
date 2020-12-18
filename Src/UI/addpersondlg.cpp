#include "addpersondlg.h"
#include "ui_addpersondlg.h"
#include <QDebug>
#include <QListView>

AddPersonDlg::AddPersonDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPersonDlg)
{
    ui->setupUi(this);
    setWindowFlags (Qt::FramelessWindowHint | Qt::Dialog);

    QListView *list = new QListView;

    ui->comboBox->setView(list);

    QString style = styleSheet() + "\nQListView::item{height:30;}";
    setStyleSheet(style);

    ui->comboBox->addItems(QStringList() << "aaaa" << "bbbbb" << "ccccc");

    qDebug() << "Style: \n" << style;

}

AddPersonDlg::~AddPersonDlg()
{
    delete ui;
}

void AddPersonDlg::on_pBtn_cancel_clicked()
{
    close();
    qDebug() << __FUNCTION__;
}
