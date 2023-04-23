#include "widget.h"
#include "ui_widget.h"
#include "rowitem.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    status = false;
    time = 0;
    timePiece = 0;
    for(int i = 0; i < 3; ++i) {
        priorities[i] = 0;
    }

    ui->tableWidget_readyQueue->horizontalHeader()->setVisible(true);
    ui->tableWidget_finishedQueue->horizontalHeader()->setVisible(true);

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

    ui->pushButton_start->setEnabled(false);
    ui->pushButton_pause->setEnabled(false);
    ui->pushButton_resume->setEnabled(false);

    ui->tableWidget_readyQueue->showColumn(3);
    ui->tableWidget_readyQueue->hideColumn(4);
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
    int arriveTime, runTime, priority;
    if(ui->comboBox->currentIndex() == 0) {
        if(timePiece == 0) {
            timePiece = ui->lineEdit_timePiece->text().toInt();
        }
        arriveTime = ui->lineEdit_arriveTime->text().toInt();
        runTime = ui->lineEdit_runTime->text().toInt();
        priority = ui->lineEdit_priority_1->text().toInt();

        if(!(timePiece && arriveTime && runTime && priority)) {
            timePiece = 0;
            QMessageBox::information(this, "警告", "请输入完整信息！");
            return;
        }
        ui->lineEdit_timePiece->setEnabled(false);

        RowItem ri(ris.size() + 1, arriveTime, runTime, priority, 0);
        ris.push_back(ri);

        ui->lineEdit_priority_1->clear();
    }
    else if(ui->comboBox->currentIndex() == 1){
        if(priorities[0] == 0) {
            priorities[0] = ui->lineEdit_priority_1->text().toInt();
            priorities[1] = ui->lineEdit_priority_2->text().toInt();
            priorities[2] = ui->lineEdit_priority_3->text().toInt();
        }
        arriveTime = ui->lineEdit_arriveTime->text().toInt();
        runTime = ui->lineEdit_runTime->text().toInt();

        if(!(priorities[0] && priorities[1] && priorities[2] && arriveTime && runTime)) {
            for(int i = 0; i < 3; ++i) {
                priorities[i] = 0;
            }
            QMessageBox::information(this, "警告", "请输入完整信息！");
            return;
        }
        ui->lineEdit_priority_1->setEnabled(false);
        ui->lineEdit_priority_2->setEnabled(false);
        ui->lineEdit_priority_3->setEnabled(false);

        RowItem ri(ris.size() + 1, arriveTime, runTime, 0, 1);
        ris.push_back(ri);
    }

    int r = ui->tableWidget_readyQueue->rowCount();
    ui->tableWidget_readyQueue->insertRow(r);
    ui->tableWidget_readyQueue->setItem(r, 0, new QTableWidgetItem(QString::number(ris.back().index)));
    ui->tableWidget_readyQueue->setItem(r, 1, new QTableWidgetItem(QString::number(ris.back().arriveTime)));
    ui->tableWidget_readyQueue->setItem(r, 2, new QTableWidgetItem(QString::number(ris.back().runTime)));
    ui->tableWidget_readyQueue->setItem(r, 3, new QTableWidgetItem(QString::number(ris.back().priority)));
    ui->tableWidget_readyQueue->setItem(r, 4, new QTableWidgetItem(QString::number(ris.back().currentQueue)));
    ui->tableWidget_readyQueue->setCellWidget(r, 5, ris.back().progressBar);

    for(int j = 0; j < 4; ++j) {
        ui->tableWidget_readyQueue->item(r, j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }

    ui->lineEdit_arriveTime->clear();
    ui->lineEdit_runTime->clear();

//    for(int i = 0; i < ris.size(); ++i) {
//        if(!vis[i]) {
//            int index = ris[i].index - 1;
//            ui->tableWidget_readyQueue->insertRow(index);
//            ui->tableWidget_readyQueue->setItem(index, 0, new QTableWidgetItem(QString::number(ris[i].index)));
//            ui->tableWidget_readyQueue->setItem(index, 1, new QTableWidgetItem(QString::number(ris[i].arriveTime)));
//            ui->tableWidget_readyQueue->setItem(index, 2, new QTableWidgetItem(QString::number(ris[i].runTime)));
//            ui->tableWidget_readyQueue->setItem(index, 3, new QTableWidgetItem(QString::number(ris[i].priority)));
//            ui->tableWidget_readyQueue->setItem(index, 4, new QTableWidgetItem(QString::number(ris[i].currentQueue)));
//            ui->tableWidget_readyQueue->setCellWidget(index, 5, ris[i].progressBar);

//            vis[i] = true;
//        }

//        //元素居中
//        for(int j = 0; j < 4; ++j) {
//            ui->tableWidget_readyQueue->item(i, j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
//        }
//    }

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

    ui->pushButton_start->setEnabled(true);
}

void Widget::on_pushButton_reset_clicked()
{
    ui->pushButton_pause->setEnabled(false);
    ui->pushButton_start->setEnabled(false);

    ui->lineEdit_arriveTime->clear();
    ui->lineEdit_priority_1->clear();
    ui->lineEdit_priority_2->clear();
    ui->lineEdit_priority_3->clear();
    ui->lineEdit_runTime->clear();
    ui->lineEdit_timePiece->clear();
    while(ui->tableWidget_readyQueue->rowCount()) {
        ui->tableWidget_readyQueue->removeRow(0);
    }
    while(ui->tableWidget_finishedQueue->rowCount()) {
        ui->tableWidget_finishedQueue->removeRow(0);
    }

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
    timePiece = 0;
    for(int i = 0; i < 3; ++i) {
        priorities[i] = 0;
    }
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
    ui->pushButton_start->setEnabled(true);
}

void Widget::on_pushButton_reset_2_clicked()
{
    ui->pushButton_pause->setEnabled(false);
    ui->pushButton_start->setEnabled(false);

    ui->lineEdit_arriveTime_2->clear();
    ui->lineEdit_runTime_2->clear();
    while(ui->tableWidget_readyQueue->rowCount()) {
        ui->tableWidget_readyQueue->removeRow(0);
    }
    while(ui->tableWidget_finishedQueue->rowCount()) {
        ui->tableWidget_finishedQueue->removeRow(0);
    }

    ui->comboBox_2->setEnabled(true);
    ui->pushButton_select_2->setEnabled(true);
    ui->tableWidget_readyQueue->setEnabled(false);
    ui->tableWidget_finishedQueue->setEnabled(false);
    ui->groupBox_jb->setEnabled(false);
    ui->pushButton_reset_2->setEnabled(false);
    ui->tabWidget->setTabEnabled(0, true);

    ris.clear();
}

void Widget::on_pushButton_add_2_clicked()
{
    int arriveTime, runTime;
    arriveTime = ui->lineEdit_arriveTime_2->text().toInt();
    runTime = ui->lineEdit_runTime_2->text().toInt();
    if(!(arriveTime && runTime)) {
        QMessageBox::information(this, "警告", "请输入完整信息！");
        return;
    }
    RowItem ri(ris.size() + 1, arriveTime, runTime, 0, 0);
    ris.push_back(ri);

    int r = ui->tableWidget_readyQueue->rowCount();
    ui->tableWidget_readyQueue->insertRow(r);
    ui->tableWidget_readyQueue->setItem(r, 0, new QTableWidgetItem(QString::number(ris.back().index)));
    ui->tableWidget_readyQueue->setItem(r, 1, new QTableWidgetItem(QString::number(ris.back().arriveTime)));
    ui->tableWidget_readyQueue->setItem(r, 2, new QTableWidgetItem(QString::number(ris.back().runTime)));
    ui->tableWidget_readyQueue->setItem(r, 3, new QTableWidgetItem(QString::number(ris.back().priority)));
    ui->tableWidget_readyQueue->setItem(r, 4, new QTableWidgetItem(QString::number(ris.back().currentQueue)));
    ui->tableWidget_readyQueue->setCellWidget(r, 5, ris.back().progressBar);

    for(int j = 0; j < 4; ++j) {
        ui->tableWidget_readyQueue->item(r, j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }

    ui->lineEdit_arriveTime_2->clear();
    ui->lineEdit_runTime_2->clear();
}

void Widget::on_tabWidget_tabBarClicked(int index)
{
    if(ui->tabWidget->tabBar()->currentIndex() == 1) {
        if(ui->comboBox->currentIndex() == 0) {
            ui->tableWidget_readyQueue->showColumn(3);
            ui->tableWidget_readyQueue->hideColumn(4);
        }
        else if(ui->comboBox->currentIndex() == 1) {
            ui->tableWidget_readyQueue->hideColumn(3);
            ui->tableWidget_readyQueue->showColumn(4);
        }
    }
    else if(ui->tabWidget->tabBar()->currentIndex() == 0) {
        ui->tableWidget_readyQueue->hideColumn(3);
        ui->tableWidget_readyQueue->hideColumn(4);
    }
}

void Widget::on_pushButton_delete_2_clicked()
{
    int rmv = ui->tableWidget_readyQueue->currentRow();
    ui->tableWidget_readyQueue->removeRow(rmv);
    ris.erase(ris.begin() + rmv, ris.begin() + rmv + 1);
    for(int i = 0; i < ris.size(); ++i) {
       ris[i].index = i + 1;
       ui->tableWidget_readyQueue->setItem(i, 0, new QTableWidgetItem(QString::number(ris[i].index)));
       ui->tableWidget_readyQueue->item(i, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
}

void Widget::run() {
    while(true) {
        if(status) {
            ui->lcdNumber->display(QString::number(time));

            if(ui->tabWidget->tabBar()->currentIndex() == 0) {
                if(ui->comboBox->currentIndex() == 0) {

                }
                else if(ui->comboBox->currentIndex() == 1) {

                }
            }
            else if(ui->tabWidget->tabBar()->currentIndex() == 1) {
                if(ui->comboBox_2->currentIndex() == 0) {

                }
                else if(ui->comboBox_2->currentIndex() == 1) {

                }
                else if(ui->comboBox_2->currentIndex() == 2) {

                }
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
            time++;
        }
    }
}

void Widget::on_pushButton_start_clicked()
{
    status = true;
    ui->pushButton_start->setEnabled(false);
    ui->pushButton_pause->setEnabled(true);

    std::thread my_thread(run);
    my_thread.detach();

}

void Widget::on_pushButton_pause_clicked()
{
    status = false;
    ui->pushButton_start->setEnabled(true);
    ui->pushButton_pause->setEnabled(false);
    ui->pushButton_resume->setEnabled(true);
}

void Widget::on_pushButton_resume_clicked()
{
    status = true;
    ui->pushButton_pause->setEnabled(true);
    ui->pushButton_resume->setEnabled(false);
}
