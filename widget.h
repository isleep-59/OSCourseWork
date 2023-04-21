#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void prcs_hide();
    void prcs_show();
    void prcs_clear();
    void jb_clear();

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_add_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_select_clicked();

    void on_pushButton_reset_clicked();


    void on_pushButton_select_2_clicked();

    void on_pushButton_reset_2_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
