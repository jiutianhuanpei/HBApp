#ifndef ADDUSERWGT_H
#define ADDUSERWGT_H

#include <QWidget>

namespace Ui {
class AddUserWgt;
}

class AddUserWgt : public QWidget
{
    Q_OBJECT

public:
    explicit AddUserWgt(QWidget *parent = nullptr);
    ~AddUserWgt();

private slots:
    void on_pBtn_confirm_clicked();

    void on_pBtn_cancel_clicked();

private:
    Ui::AddUserWgt *ui;
};

#endif // ADDUSERWGT_H
