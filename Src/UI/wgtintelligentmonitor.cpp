#include "wgtintelligentmonitor.h"
#include "ui_wgtintelligentmonitor.h"

WgtIntelligentMonitor::WgtIntelligentMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WgtIntelligentMonitor)
{

    ui->setupUi(this);
    ui->widget->setVisible(true);

    m_addPerson = new AddPersonDlg(this);

}

WgtIntelligentMonitor::~WgtIntelligentMonitor()
{
    delete ui;
}

void WgtIntelligentMonitor::on_pushButton_clicked()
{

    m_addPerson->exec ();
}
