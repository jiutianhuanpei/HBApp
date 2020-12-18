#ifndef HYPAGENAVIGATOR_H
#define HYPAGENAVIGATOR_H

#include <QWidget>
#include <QButtonGroup>
#include <QPushButton>

namespace Ui {
class HYPageNavigator;
}

class HYPageNavigator : public QWidget
{
    Q_OBJECT

public:
    explicit HYPageNavigator(QWidget *parent = nullptr);
    ~HYPageNavigator();

    //设置总页数
    void setPageNum(const int num);

    //设置当前页数，从 1 开始
    void setCurrentPage(const int page, bool sendSignal = true);
    int currentPage() { return m_currentPage;};


signals:
    void signal_pageNavigatorChanged(int pageNum);

private:
    Ui::HYPageNavigator *ui;
    QButtonGroup *m_btns;
    int m_currentPage = 1;

    int m_beginPageNum = 1;
    int m_maxPageNum;


private:

    void _InitinalizeWgts();
    void _InitinalizeConnects();


    QPushButton *m_btnAt(const int index);


private slots:
    void slot_didClickedBtn(int index);


    void on_pBtn_goto_clicked();
    void on_pBtn_right_clicked();
    void on_pBtn_left_clicked();
};

#endif // HYPAGENAVIGATOR_H
