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

private:
    Ui::AddUserWgt *ui;
};

#endif // ADDUSERWGT_H
