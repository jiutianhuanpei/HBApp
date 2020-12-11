#ifndef WGTINTELLIGENTMONITOR_H
#define WGTINTELLIGENTMONITOR_H

#include <QWidget>

namespace Ui {
class WgtIntelligentMonitor;
}

class WgtIntelligentMonitor : public QWidget
{
    Q_OBJECT

public:
    explicit WgtIntelligentMonitor(QWidget *parent = nullptr);
    ~WgtIntelligentMonitor();

private:
    Ui::WgtIntelligentMonitor *ui;
};

#endif // WGTINTELLIGENTMONITOR_H
