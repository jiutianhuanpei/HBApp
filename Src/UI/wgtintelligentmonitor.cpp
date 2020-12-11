#include "wgtintelligentmonitor.h"
#include "ui_wgtintelligentmonitor.h"

WgtIntelligentMonitor::WgtIntelligentMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WgtIntelligentMonitor)
{
    ui->setupUi(this);
    ui->widget->setVisible(true);
}

WgtIntelligentMonitor::~WgtIntelligentMonitor()
{
    delete ui;
}
