#include "hypagenavigator.h"
#include "ui_hypagenavigator.h"
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>

const int FoldingIndex = 8;

HYPageNavigator::HYPageNavigator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HYPageNavigator)
{
    ui->setupUi(this);

    _InitinalizeWgts();
    _InitinalizeConnects();
    setPageNum(11);
}

HYPageNavigator::~HYPageNavigator()
{
    delete ui;
}

void HYPageNavigator::setPageNum(const int num)
{
    m_maxPageNum = num;

    for (int i = 1; i <= 10; ++i) {

        QPushButton *btn = static_cast<QPushButton *>(m_btns->buttons()[i-1]);
        btn->setVisible(i <= num);

        if (num <= 10)
        {
            //没有折叠按钮
            btn->setText(QString("%1").arg(i));
        }
        //有折叠按钮
        else if (i < FoldingIndex)
        {
            btn->setText(QString("%1").arg(i));
        }
        else if (i == FoldingIndex) {
            btn->setText("...");
        }
        else if (i == FoldingIndex + 1)
        {
            btn->setText(QString("%1").arg(m_maxPageNum - 1));
        }
        else
        {
            btn->setText(QString("%1").arg(m_maxPageNum));
        }
    }
}

void HYPageNavigator::setCurrentPage(const int page)
{
    if (m_btns->buttons().count() == 0)
    {
        qDebug() << "Have no btn";
        return;
    }
    m_currentPage = page;
    qDebug() << "Currentpage: " << page;

    foreach (auto it, m_btns->buttons()) {
        QPushButton *btn = static_cast<QPushButton *>(it);
        int num = btn->text().toInt();
        btn->setProperty("currentPage", num == page);
        btn->setStyleSheet("/**/");
    }

    qDebug() << "Enable: " << (m_currentPage == 1) << (m_currentPage == m_maxPageNum);

    ui->pBtn_left->setEnabled(m_currentPage != 1);
    ui->pBtn_right->setEnabled(m_currentPage != m_maxPageNum);
}

void HYPageNavigator::_InitinalizeWgts()
{

    m_btns = new QButtonGroup;
    m_btns->setExclusive(true);

    for (int i = 1; i <= 10; ++i) {

        QPushButton *btn = new QPushButton;
        btn->setProperty("page", true);
        btn->setText(QString("%1").arg(i));
        ui->btnLayout->addWidget(btn);
        m_btns->addButton(btn, i);
    }

    m_btns->buttons().first()->setProperty("currentPage", true);
    setCurrentPage(1);

}

void HYPageNavigator::_InitinalizeConnects()
{
    connect(m_btns, qOverload<int>(&QButtonGroup::buttonClicked), this, &HYPageNavigator::slot_didClickedBtn);
}

void HYPageNavigator::slot_didClickedBtn(int index)
{
    if (m_btns->buttons().count() == 0)
        return;

    setCurrentPage(index);
}

void HYPageNavigator::on_pBtn_goto_clicked()
{

}

void HYPageNavigator::on_pBtn_right_clicked()
{
    if (m_currentPage <= m_maxPageNum - 1)
        m_currentPage++;
    setCurrentPage(m_currentPage);
}

void HYPageNavigator::on_pBtn_left_clicked()
{
    if (m_currentPage > 1)
        m_currentPage--;

    setCurrentPage(m_currentPage);
}
