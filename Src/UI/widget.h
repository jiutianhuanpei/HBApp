#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void log(const QString msg);

private slots:
    void on_pBtn_add_clicked();

    void on_pBtn_delete_clicked();

    void on_pBtn_modify_clicked();

    void on_pBtn_log_clicked();

private:
    Ui::Widget *ui;


};

#endif // WIDGET_H
