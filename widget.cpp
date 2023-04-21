#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->tableWidget_readyQueue->setEnabled(false);

    ui->groupBox_prcs->setEnabled(false);
    ui->pushButton_reset->setEnabled((false));
    prcs_hide();


    ui->groupBox_jb->setEnabled(false);
    ui->pushButton_reset_2->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::prcs_hide() {
    ui->lineEdit_priority_2->hide();
    ui->lineEdit_priority_3->hide();
    ui->label_priority_1->hide();
    ui->label_priority_2->hide();
    ui->label_priority_3->hide();
}

void Widget::prcs_show() {
    ui->lineEdit_priority_2->show();
    ui->lineEdit_priority_3->show();
    ui->label_priority_1->show();
    ui->label_priority_2->show();
    ui->label_priority_3->show();
}

void Widget::prcs_clear() {
    ui->lineEdit_arriveTime->clear();
    ui->lineEdit_priority_1->clear();
    ui->lineEdit_priority_2->clear();
    ui->lineEdit_priority_3->clear();
    ui->lineEdit_runTime->clear();
    ui->lineEdit_timePiece->clear();
}

void Widget::jb_clear() {

}

void Widget::on_comboBox_activated(const QString &arg1)
{
    if(ui->comboBox->currentIndex() == 0) {
        prcs_hide();
        ui->tableWidget_readyQueue->showColumn(3);
    }
    else if(ui->comboBox->currentIndex() == 1) {
        prcs_show();
        ui->tableWidget_readyQueue->hideColumn(3);
    }
}

void Widget::on_pushButton_add_clicked()
{
    QString arriveTime, runTime, timePiece, priority;
    arriveTime = ui->lineEdit_arriveTime->text();
    runTime = ui->lineEdit_runTime->text();
    timePiece = ui->lineEdit_timePiece->text();
    priority = ui->lineEdit_priority_1->text();

    if(arriveTime.length() == 0 || runTime.length() == 0 || timePiece.length() == 0 ||priority.length() == 0) {
        QMessageBox::information(this, "Warning", "请完善输入数据！");
        return;
    }

    int index = ui->tableWidget_readyQueue->rowCount();
    QString index_s(new QChar(char(index + 1 + '0')));
    ui->tableWidget_readyQueue->insertRow(index);
    ui->tableWidget_readyQueue->setItem(index, 0, new QTableWidgetItem(index_s.left(1)));
    ui->tableWidget_readyQueue->setItem(index, 1, new QTableWidgetItem(arriveTime));
    ui->tableWidget_readyQueue->setItem(index, 2, new QTableWidgetItem(runTime));

    if(ui->comboBox->currentIndex() == 0)
        ui->tableWidget_readyQueue->setItem(index, 3, new QTableWidgetItem(priority));

    prcs_clear();
}



void Widget::on_pushButton_delete_clicked()
{
    ui->tableWidget_readyQueue->removeRow(ui->tableWidget_readyQueue->currentRow());
}

void Widget::on_pushButton_select_clicked()
{
    ui->comboBox->setEnabled(false);
    ui->pushButton_select->setEnabled(false);
    ui->tableWidget_readyQueue->setEnabled(true);
    ui->groupBox_prcs->setEnabled(true);
    ui->pushButton_reset->setEnabled(true);
    ui->tabWidget->setTabEnabled(1, false);
}

void Widget::on_pushButton_reset_clicked()
{
    prcs_clear();
    ui->comboBox->setEnabled(true);
    ui->pushButton_select->setEnabled(true);
    ui->tableWidget_readyQueue->setEnabled(false);
    ui->groupBox_prcs->setEnabled(false);
    ui->pushButton_reset->setEnabled(false);
    ui->tabWidget->setTabEnabled(1, true);
}

void Widget::on_pushButton_select_2_clicked()
{
    ui->comboBox_2->setEnabled(false);
    ui->pushButton_select_2->setEnabled(false);
    ui->tableWidget_readyQueue->setEnabled(true);
    ui->groupBox_jb->setEnabled(true);
    ui->pushButton_reset_2->setEnabled(true);
    ui->tabWidget->setTabEnabled(0, false);
}

void Widget::on_pushButton_reset_2_clicked()
{
    jb_clear();
    ui->comboBox_2->setEnabled(true);
    ui->pushButton_select_2->setEnabled(true);
    ui->tableWidget_readyQueue->setEnabled(false);
    ui->groupBox_jb->setEnabled(false);
    ui->pushButton_reset_2->setEnabled(false);
    ui->tabWidget->setTabEnabled(0, true);
}
