#include "hypagenavigator.h"
#include "ui_hypagenavigator.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QComboBox>
#include <QRegExpValidator>

const int FastSmallerIndex = 2;
const int CurrentShowIndex = 5;
const int FastBiggerIndex = 8;

HYPageNavigator::HYPageNavigator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HYPageNavigator)
{

    ui->setupUi(this);

    _InitinalizeWgts();
    _InitinalizeConnects();
    setPageNum(9000);
}

HYPageNavigator::~HYPageNavigator()
{
    delete ui;
}

void HYPageNavigator::setPageNum(const int num)
{
    m_maxPageNum = num;
    setCurrentPage(1, false);
}

void HYPageNavigator::_InitinalizeWgts()
{

    m_btns = new QButtonGroup;
    m_btns->setExclusive(true);

    for (int i = 1; i <= 9; ++i) {

        QPushButton *btn = new QPushButton;
        btn->setProperty("page", true);
        ui->btnLayout->addWidget(btn);
        m_btns->addButton(btn, i);
    }

    QRegExp exp("[1-9][0-9]*");
    QRegExpValidator *val = new QRegExpValidator(exp, this);
    ui->lineEdit->setValidator(val);

}

void HYPageNavigator::_InitinalizeConnects()
{
    connect(m_btns, qOverload<int>(&QButtonGroup::buttonClicked), this, &HYPageNavigator::slot_didClickedBtn);
}

void HYPageNavigator::slot_didClickedBtn(int index)
{
    if (m_btns->buttons().count() == 0)
        return;

    bool ret;
    int num = m_btns->buttons()[index-1]->text().toInt(&ret);
    if (!ret)
    {
        if (index == FastSmallerIndex)
            num = m_currentPage - 5;
        else if (index == FastBiggerIndex)
            num = m_currentPage + 5;
    }
    setCurrentPage(num);
}

void HYPageNavigator::on_pBtn_goto_clicked()
{
    int toPage = ui->lineEdit->text().toInt();
    if (toPage < 1 || toPage > m_maxPageNum)
        return;
    setCurrentPage(toPage);

    qDebug() << "ToPage: " << toPage;
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


void HYPageNavigator::setCurrentPage(const int page, bool sendSignal)
{

    //由于有快速进、退5页的问题，所以当 num > 5 页时，index == 2/8的两个按钮就要显示了
    //因为按钮一共有 9 个，所以 5 < num < 9 时，需要隐藏些按钮
    m_currentPage = page;
    do {

        if (m_maxPageNum <= 5)
        {
            m_btnAt(1)->setVisible(false);
            m_btnAt(2)->setVisible(false);
            m_btnAt(8)->setVisible(false);
            m_btnAt(9)->setVisible(false);

            for (int index = 1; index <= 9; ++index) {

                QPushButton *btn = m_btnAt(index);

                bool canShow = (index >= 3) && (index < m_maxPageNum + 3);

                btn->setVisible(canShow);
                if (canShow)
                {
                    btn->setText(QString("%1").arg(index - 3 + 1));
                }
                else {
                   btn->setText("");
                }
            }
            break;
        }

        for (int index = 1; index <= 9; ++index) {

            QPushButton *btn = m_btnAt(index);

            if (index == 1)
            {
                btn->setVisible(true);
                btn->setText("1");
            }
            else if (index == 2)
            {
                btn->setVisible(page > 4);
                btn->setText("...");
            }
            else if (index == 8)
            {
                btn->setVisible(page < (m_maxPageNum - 3));
                btn->setText("...");
            }
            else if (index == 9)
            {
                btn->setVisible(true);
                btn->setText(QString("%1").arg(m_maxPageNum));
            }
            else
            {

                QList<int> centerNumArray;
                if (page == 1)
                {
                    for (int i = 1; i <= qMin(m_maxPageNum-2, 5); ++i) {
                        centerNumArray.append(i + 1);
                    }
                }
                else if (page == m_maxPageNum)
                {
                    for (int i = m_maxPageNum - 1; i >= qMax((m_maxPageNum - 5), 2) ; --i) {
                        centerNumArray.insert(0, i);
                    }
                }
                else
                {
                    if (page <= 4)
                    {
                        for (int i = 2; i <= page; i++)
                        {
                            centerNumArray.append(i);
                        }

                        for (int i = page + 1; i < m_maxPageNum && centerNumArray.count() < 5; i++)
                        {
                            centerNumArray.append(i);
                        }
                    }
                    else if (page >= m_maxPageNum - 3)
                    {
                        for (int i = m_maxPageNum - 1; i >= 2 && centerNumArray.count() < 5; i--)
                        {
                            centerNumArray.insert(0, i);
                        }
                    }
                    else
                    {
                        for (int i = page - 2; centerNumArray.count() < 5; i++)
                        {
                            centerNumArray.append(i);
                        }
                    }
                }


                for (int index = 3; index <= 7; ++index) {

                    QPushButton *btn = m_btnAt(index);

                    bool canShow = (index - 3) < centerNumArray.count();

                    btn->setVisible(canShow);

                    if (canShow)
                        btn->setText(QString("%1").arg(centerNumArray[index - 3]));
                }

            }
        }

    } while (0);


	foreach(auto it, m_btns->buttons()) {
		QPushButton *btn = static_cast<QPushButton *>(it);

		QString numStr = btn->text();

        bool isCurrentPage = numStr == QString("%1").arg(page);

        btn->setProperty("currentPage", isCurrentPage ? "true" : "");
        btn->style()->polish(btn);
	}


    if (sendSignal)
        emit signal_pageNavigatorChanged(m_currentPage);
}

QPushButton *HYPageNavigator::m_btnAt(const int index)
{
    QPushButton *btn = static_cast<QPushButton *>(m_btns->button(index));
    return btn;
}
