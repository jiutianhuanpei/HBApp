#include "adduserwgt.h"
#include "ui_adduserwgt.h"

AddUserWgt::AddUserWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddUserWgt)
{
    ui->setupUi(this);
}

AddUserWgt::~AddUserWgt()
{
    delete ui;
}
