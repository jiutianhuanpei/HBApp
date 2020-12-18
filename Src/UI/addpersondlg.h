#ifndef ADDPERSONDLG_H
#define ADDPERSONDLG_H

#include <QDialog>

namespace Ui {
class AddPersonDlg;
}

class AddPersonDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddPersonDlg(QWidget *parent = nullptr);
    ~AddPersonDlg();

private slots:
    void on_pBtn_cancel_clicked();

private:
    Ui::AddPersonDlg *ui;
};

#endif // ADDPERSONDLG_H
