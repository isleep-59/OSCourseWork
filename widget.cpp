#include "widget.h"
#include "ui_widget.h"
#include "rowitem.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    timePiece = 0;
    for(int i = 0; i < 3; ++i) {
        priorities[i] = 0;
    }

    ui->tableWidget_readyQueue->showColumn(3);
    ui->tableWidget_readyQueue->hideColumn(4);

    ui->tableWidget_readyQueue->setEnabled(false);
    ui->tableWidget_finishedQueue->setEnabled(false);

    ui->groupBox_prcs->setEnabled(false);
    ui->pushButton_reset->setEnabled((false));
    ui->lineEdit_priority_2->hide();
    ui->lineEdit_priority_3->hide();
    ui->label_priority_1->hide();
    ui->label_priority_2->hide();
    ui->label_priority_3->hide();


    ui->groupBox_jb->setEnabled(false);
    ui->pushButton_reset_2->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_comboBox_activated(const QString &arg1)
{
    if(ui->comboBox->currentIndex() == 0) {
        ui->lineEdit_priority_2->hide();
        ui->lineEdit_priority_3->hide();
        ui->label_priority_1->hide();
        ui->label_priority_2->hide();
        ui->label_priority_3->hide();
        ui->label_11->show();
        ui->lineEdit_timePiece->show();
        ui->label_12->setText("优先级：");

        ui->tableWidget_readyQueue->showColumn(3);
        ui->tableWidget_readyQueue->hideColumn(4);
    }
    else if(ui->comboBox->currentIndex() == 1) {
        ui->lineEdit_priority_2->show();
        ui->lineEdit_priority_3->show();
        ui->label_priority_1->show();
        ui->label_priority_2->show();
        ui->label_priority_3->show();
        ui->label_11->hide();
        ui->lineEdit_timePiece->hide();
        ui->label_12->setText("队列时间片：");

        ui->tableWidget_readyQueue->hideColumn(3);
        ui->tableWidget_readyQueue->showColumn(4);
    }
}

void Widget::on_pushButton_add_clicked()
{
    QString arriveTime, runTime, priority;
    if(ui->comboBox->currentIndex() == 0) {
        if(timePiece == 0) {
            timePiece = ui->lineEdit_timePiece->text().toInt();
            ui->lineEdit_timePiece->setEnabled(false);
        }
        arriveTime = ui->lineEdit_arriveTime->text();
        runTime = ui->lineEdit_runTime->text();
        priority = ui->lineEdit_priority_1->text();
        RowItem ri(ris.size() + 1, arriveTime.toInt(), runTime.toInt(), priority.toInt(), 0);
        ris.push_back(ri);
        vis.push_back(false);

        ui->lineEdit_priority_1->clear();
    }
    else if(ui->comboBox->currentIndex() == 1){
        if(priorities[0] == 0) {
            priorities[0] = ui->lineEdit_priority_1->text().toInt();
            priorities[1] = ui->lineEdit_priority_2->text().toInt();
            priorities[2] = ui->lineEdit_priority_3->text().toInt();

            ui->lineEdit_priority_1->setEnabled(false);
            ui->lineEdit_priority_2->setEnabled(false);
            ui->lineEdit_priority_3->setEnabled(false);
        }
        arriveTime = ui->lineEdit_arriveTime->text();
        runTime = ui->lineEdit_runTime->text();
        RowItem ri(ris.size() + 1, arriveTime.toInt(), runTime.toInt(), 0, 1);
        ris.push_back(ri);
        vis.push_back(false);
    }

    for(int i = 0; i < ris.size(); ++i) {
        if(!vis[i]) {
            int index = ris[i].index - 1;
            ui->tableWidget_readyQueue->insertRow(index);
            ui->tableWidget_readyQueue->setItem(index, 0, new QTableWidgetItem(QString::number(ris[i].index)));
            ui->tableWidget_readyQueue->setItem(index, 1, new QTableWidgetItem(QString::number(ris[i].arriveTime)));
            ui->tableWidget_readyQueue->setItem(index, 2, new QTableWidgetItem(QString::number(ris[i].runTime)));
            ui->tableWidget_readyQueue->setItem(index, 3, new QTableWidgetItem(QString::number(ris[i].priority)));
            ui->tableWidget_readyQueue->setItem(index, 4, new QTableWidgetItem(QString::number(ris[i].currentQueue)));
            ui->tableWidget_readyQueue->setCellWidget(index, 5, ris[i].progressBar);

            vis[i] = true;
        }

        //元素居中
        for(int j = 0; j < 4; ++j) {
            ui->tableWidget_readyQueue->item(i, j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }

    ui->lineEdit_arriveTime->clear();
    ui->lineEdit_runTime->clear();
//    ui->lineEdit_priority_1->clear();
//    ui->lineEdit_priority_2->clear();
//    ui->lineEdit_priority_3->clear();
//    ui->lineEdit_timePiece->clear();
}

void Widget::on_pushButton_delete_clicked()
{
    int rmv = ui->tableWidget_readyQueue->currentRow();
    ui->tableWidget_readyQueue->removeRow(rmv);
    ris.erase(ris.begin() + rmv, ris.begin() + rmv + 1);
    vis.erase(vis.begin() + rmv, vis.begin() + rmv + 1);
    for(int i = 0; i < ris.size(); ++i) {
       ris[i].index = i + 1;
       ui->tableWidget_readyQueue->setItem(i, 0, new QTableWidgetItem(QString::number(ris[i].index)));
       ui->tableWidget_readyQueue->item(i, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
}

void Widget::on_pushButton_select_clicked()
{
    ui->comboBox->setEnabled(false);
    ui->pushButton_select->setEnabled(false);
    ui->tableWidget_readyQueue->setEnabled(true);
    ui->tableWidget_finishedQueue->setEnabled(true);
    ui->groupBox_prcs->setEnabled(true);
    ui->pushButton_reset->setEnabled(true);
    ui->tabWidget->setTabEnabled(1, false);

    if(ui->comboBox->currentIndex() == 0) {

    }
    else if(ui->comboBox->currentIndex() == 1){

    }
}

void Widget::on_pushButton_reset_clicked()
{
    ui->lineEdit_arriveTime->clear();
    ui->lineEdit_priority_1->clear();
    ui->lineEdit_priority_2->clear();
    ui->lineEdit_priority_3->clear();
    ui->lineEdit_runTime->clear();
    ui->lineEdit_timePiece->clear();
    ui->tableWidget_readyQueue->clear();
    ui->tableWidget_finishedQueue->clear();

    ui->comboBox->setEnabled(true);
    ui->pushButton_select->setEnabled(true);
    ui->tableWidget_readyQueue->setEnabled(false);
    ui->tableWidget_finishedQueue->setEnabled(false);
    ui->groupBox_prcs->setEnabled(false);
    ui->pushButton_reset->setEnabled(false);
    ui->tabWidget->setTabEnabled(1, true);
    ui->lineEdit_timePiece->setEnabled(true);
    ui->lineEdit_priority_1->setEnabled(true);
    ui->lineEdit_priority_2->setEnabled(true);
    ui->lineEdit_priority_3->setEnabled(true);

    ris.clear();
    vis.clear();
}

void Widget::on_pushButton_select_2_clicked()
{
    ui->comboBox_2->setEnabled(false);
    ui->pushButton_select_2->setEnabled(false);
    ui->tableWidget_readyQueue->setEnabled(true);
    ui->tableWidget_finishedQueue->setEnabled(true);
    ui->groupBox_jb->setEnabled(true);
    ui->pushButton_reset_2->setEnabled(true);
    ui->tabWidget->setTabEnabled(0, false);
}

void Widget::on_pushButton_reset_2_clicked()
{
    ui->lineEdit_arriveTime_2->clear();
    ui->lineEdit_runTime_2->clear();
    ui->lineEdit_timePiece_2->clear();

    ui->comboBox_2->setEnabled(true);
    ui->pushButton_select_2->setEnabled(true);
    ui->tableWidget_readyQueue->setEnabled(false);
    ui->tableWidget_finishedQueue->setEnabled(false);
    ui->groupBox_jb->setEnabled(false);
    ui->pushButton_reset_2->setEnabled(false);
    ui->tabWidget->setTabEnabled(0, true);
}
