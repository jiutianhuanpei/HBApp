#ifndef WGTINTELLIGENTMONITOR_H
#define WGTINTELLIGENTMONITOR_H

#include <QWidget>
#include "addpersondlg.h"

namespace Ui {
class WgtIntelligentMonitor;
}

class WgtIntelligentMonitor : public QWidget
{
    Q_OBJECT

public:
    explicit WgtIntelligentMonitor(QWidget *parent = nullptr);
    ~WgtIntelligentMonitor();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WgtIntelligentMonitor *ui;

    AddPersonDlg *m_addPerson;
};

#endif // WGTINTELLIGENTMONITOR_H
