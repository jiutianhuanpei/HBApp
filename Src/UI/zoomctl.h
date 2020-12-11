#ifndef ZOOMCTL_H
#define ZOOMCTL_H

#include <QWidget>
#include "uiheader.h"

namespace Ui {
class ZoomCtl;
}

class ZoomCtl : public QWidget
{
    Q_OBJECT

public:
    explicit ZoomCtl(QWidget *parent = nullptr);
    ~ZoomCtl();


signals:
    void signal_didClicked(WindowZoom zoomType);

private:
    Ui::ZoomCtl *ui;
};

#endif // ZOOMCTL_H
