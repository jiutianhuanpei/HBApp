#ifndef HYPAGENAVIGATOR_H
#define HYPAGENAVIGATOR_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class HYPageNavigator;
}

class HYPageNavigator : public QWidget
{
    Q_OBJECT

public:
    explicit HYPageNavigator(QWidget *parent = nullptr);
    ~HYPageNavigator();

    void setPageNum(const int num);

    void setCurrentPage(const int page);
    int currentPage() { return m_currentPage;};


signals:
    void signal_pageSizeChanged(int size);

private:
    Ui::HYPageNavigator *ui;
    QButtonGroup *m_btns;
    int m_currentPage = 1;
    int m_maxPageNum;

    int m_pageNum = 10;

private:

    void _InitinalizeWgts();
    void _InitinalizeConnects();

private slots:
    void slot_didClickedBtn(int index);


    void on_pBtn_goto_clicked();
    void on_pBtn_right_clicked();
    void on_pBtn_left_clicked();
};

#endif // HYPAGENAVIGATOR_H
