#ifndef WIDGET_H
#define WIDGET_H

#include <windows.h>
#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <vector>
#include <queue>
#include "rowitem.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void RR();
    void MLFQ();
    void FCFS();
    void SJF();
    void HRN();

private slots:
    void timeout_slot();

    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_add_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_select_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_select_2_clicked();

    void on_pushButton_reset_2_clicked();

    void on_pushButton_add_2_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_pushButton_delete_2_clicked();

    void on_pushButton_start_clicked();

private:
    Ui::Widget *ui;
    std::vector<RowItem> ris;
    int timePiece;
    int priorities[3];
    int time;
    bool status;
    QTimer* timer;
};

#endif // WIDGET_H
