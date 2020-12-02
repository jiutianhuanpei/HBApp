#ifndef TOPBARWGT_H
#define TOPBARWGT_H

#include <QWidget>
#include <QFrame>
#include "uiheader.h"
#include <QButtonGroup>
#include "zoomcontrol.h"

namespace Ui {
class TopBarWgt;
}

class TopBarWgt : public QFrame
{
    Q_OBJECT

public:
    explicit TopBarWgt(QWidget *parent = nullptr);
    ~TopBarWgt();


    QVector<MenuIndex> visiableIndexs();
    void setCurrentIndex(MenuIndex index);


signals:
    void signal_didClickedMenu(MenuIndex index);

private:
    Ui::TopBarWgt *ui;

    ZoomControl *zc;

    QButtonGroup *m_btns;



};

#endif // TOPBARWGT_H
