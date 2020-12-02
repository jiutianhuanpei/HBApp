#include "topbarwgt.h"
#include "ui_topbarwgt.h"
#include <QDebug>
#include "../Src/MessageCenter/messagecore.h"

TopBarWgt::TopBarWgt(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TopBarWgt)
{
    ui->setupUi(this);

    qRegisterMetaType<MenuIndex>("MenuIndex");
    qRegisterMetaType<WindowZoom>("WindowZoom");

    m_btns = new QButtonGroup(this);
    m_btns->setExclusive(true);
    m_btns->addButton(ui->pBtn_BigScreen, BigScreen);
    m_btns->addButton(ui->pBtn_Monitor, Monitor);
    m_btns->addButton(ui->pBtn_PersonMgr, PersonMgr);
    m_btns->addButton(ui->pBtn_Poll, Poll);
    m_btns->addButton(ui->pBtn_Map, Map);
    m_btns->addButton(ui->pBtn_Web, Web);

    connect(m_btns, qOverload<int>(&QButtonGroup::buttonClicked), this, [&](int index) {

        MenuIndex a = (MenuIndex)index;
        emit signal_didClickedMenu(a);
    });

    connect(ui->zoomCtl, &ZoomCtl::signal_didClicked, MsgInset(), &MessageCore::signal_windowZoom);

}

TopBarWgt::~TopBarWgt()
{
    delete ui;
}

QVector<MenuIndex> TopBarWgt::visiableIndexs()
{
    QVector<MenuIndex> array;

    foreach (QAbstractButton *btn, m_btns->buttons()) {
        int index = m_btns->id(btn);
        array << (MenuIndex)index;
    }

    return array;
}

void TopBarWgt::setCurrentIndex(MenuIndex index)
{
    m_btns->button(index)->setChecked(true);
}

