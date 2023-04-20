#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lineEdit_priority_2->hide();
    ui->lineEdit_priority_3->hide();
    ui->label_priority_1->hide();
    ui->label_priority_2->hide();
    ui->label_priority_3->hide();

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
    }
    else if(ui->comboBox->currentIndex() == 1) {
        ui->lineEdit_priority_2->show();
        ui->lineEdit_priority_3->show();
        ui->label_priority_1->show();
        ui->label_priority_2->show();
        ui->label_priority_3->show();
    }
}
