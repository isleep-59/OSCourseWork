#include "widget.h"
#include "ui_widget.h"
#include "rowitem.h"

Widget::Widget(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	fin = 0;
	idx = -1;
	curTimePiece = 0;
	timer = new QTimer;
	ui->setupUi(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeout_slot()));

	status = false;
	time = 0;
	timePiece = 0;
	for (int i = 0; i < 3; ++i) {
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

	ui->tableWidget_readyQueue->showColumn(3);
	ui->tableWidget_readyQueue->hideColumn(4);
}

Widget::~Widget()
{
	delete ui;
}

void Widget::on_comboBox_activated(const QString& arg1)
{
	if (ui->comboBox->currentIndex() == 0) {
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
	else if (ui->comboBox->currentIndex() == 1) {
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
	if (ui->comboBox->currentIndex() == 0) {
		if (timePiece == 0) {
			timePiece = ui->lineEdit_timePiece->text().toInt();
		}
		arriveTime = ui->lineEdit_arriveTime->text().toInt();
		runTime = ui->lineEdit_runTime->text().toInt();
		priority = ui->lineEdit_priority_1->text().toInt();

		if (!(timePiece && runTime && priority)) {
			timePiece = 0;
			QMessageBox::information(this, "警告", "请输入完整信息！");
			return;
		}
		ui->lineEdit_timePiece->setEnabled(false);

		RowItem ri(ris.size() + 1, arriveTime, runTime, priority, 0);
		ris.push_back(ri);

		ui->lineEdit_priority_1->clear();
	}
	else if (ui->comboBox->currentIndex() == 1) {
		if (priorities[0] == 0) {
			priorities[0] = ui->lineEdit_priority_1->text().toInt();
			priorities[1] = ui->lineEdit_priority_2->text().toInt();
			priorities[2] = ui->lineEdit_priority_3->text().toInt();
		}
		arriveTime = ui->lineEdit_arriveTime->text().toInt();
		runTime = ui->lineEdit_runTime->text().toInt();

		if (!(priorities[0] && priorities[1] && priorities[2] && runTime)) {
			for (int i = 0; i < 3; ++i) {
				priorities[i] = 0;
			}
			QMessageBox::information(this, "警告", "请输入完整信息！");
			return;
		}
		ui->lineEdit_priority_1->setEnabled(false);
		ui->lineEdit_priority_2->setEnabled(false);
		ui->lineEdit_priority_3->setEnabled(false);

		RowItem ri(ris.size() + 1, arriveTime, runTime, 0, 0);
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

	for (int j = 0; j < 4; ++j) {
		ui->tableWidget_readyQueue->item(r, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	}

	ui->tableWidget_readyQueue->scrollToBottom();

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
	for (int i = 0; i < ris.size(); ++i) {
		ris[i].index = i + 1;
		ui->tableWidget_readyQueue->setItem(i, 0, new QTableWidgetItem(QString::number(ris[i].index)));
		ui->tableWidget_readyQueue->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
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
	fin = 0;
	ui->pushButton_start->setEnabled(false);

	ui->lineEdit_arriveTime->clear();
	ui->lineEdit_priority_1->clear();
	ui->lineEdit_priority_2->clear();
	ui->lineEdit_priority_3->clear();
	ui->lineEdit_runTime->clear();
	ui->lineEdit_timePiece->clear();
	while (ui->tableWidget_readyQueue->rowCount()) {
		ui->tableWidget_readyQueue->removeRow(0);
	}
	while (ui->tableWidget_finishedQueue->rowCount()) {
		ui->tableWidget_finishedQueue->removeRow(0);
	}
	ui->listWidget->clear();

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

	ui->lcdNumber->display(0);

	ris.clear();
	timePiece = 0;
	for (int i = 0; i < 3; ++i) {
		priorities[i] = 0;
	}
	time = 0;
	for (int i = 0; i <= 3; ++i) {
		while (q[i].size()) {
			q[i].pop();
		}
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
	fin = 0;
	ui->pushButton_start->setEnabled(false);

	ui->lineEdit_arriveTime_2->clear();
	ui->lineEdit_runTime_2->clear();
	while (ui->tableWidget_readyQueue->rowCount()) {
		ui->tableWidget_readyQueue->removeRow(0);
	}
	while (ui->tableWidget_finishedQueue->rowCount()) {
		ui->tableWidget_finishedQueue->removeRow(0);
	}

	ui->comboBox_2->setEnabled(true);
	ui->pushButton_select_2->setEnabled(true);
	ui->tableWidget_readyQueue->setEnabled(false);
	ui->tableWidget_finishedQueue->setEnabled(false);
	ui->groupBox_jb->setEnabled(false);
	ui->pushButton_reset_2->setEnabled(false);
	ui->tabWidget->setTabEnabled(0, true);

	ui->lcdNumber->display(0);
	ui->listWidget->clear();

	ris.clear();
	time = 0;
	for (int i = 0; i <= 3; ++i) {
		while (q[i].size()) {
			q[i].pop();
		}
	}
}

void Widget::on_pushButton_add_2_clicked()
{
	int arriveTime, runTime;
	arriveTime = ui->lineEdit_arriveTime_2->text().toInt();
	runTime = ui->lineEdit_runTime_2->text().toInt();
	if (!runTime) {
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

	for (int j = 0; j < 4; ++j) {
		ui->tableWidget_readyQueue->item(r, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	}

	ui->tableWidget_readyQueue->scrollToBottom();

	ui->lineEdit_arriveTime_2->clear();
	ui->lineEdit_runTime_2->clear();
}

void Widget::on_tabWidget_tabBarClicked(int index)
{
	if (ui->tabWidget->tabBar()->currentIndex() == 1) {
		if (ui->comboBox->currentIndex() == 0) {
			ui->tableWidget_readyQueue->showColumn(3);
			ui->tableWidget_readyQueue->hideColumn(4);
		}
		else if (ui->comboBox->currentIndex() == 1) {
			ui->tableWidget_readyQueue->hideColumn(3);
			ui->tableWidget_readyQueue->showColumn(4);
		}
	}
	else if (ui->tabWidget->tabBar()->currentIndex() == 0) {
		ui->tableWidget_readyQueue->hideColumn(3);
		ui->tableWidget_readyQueue->hideColumn(4);
	}
}

void Widget::on_pushButton_delete_2_clicked()
{
	int rmv = ui->tableWidget_readyQueue->currentRow();
	ui->tableWidget_readyQueue->removeRow(rmv);
	ris.erase(ris.begin() + rmv, ris.begin() + rmv + 1);
	for (int i = 0; i < ris.size(); ++i) {
		ris[i].index = i + 1;
		ui->tableWidget_readyQueue->setItem(i, 0, new QTableWidgetItem(QString::number(ris[i].index)));
		ui->tableWidget_readyQueue->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	}
}

void Widget::timeout_slot() {
	ui->lcdNumber->display(QString::number(time));
	if (ui->tabWidget->tabBar()->currentIndex() == 0) {
		if (ui->comboBox->currentIndex() == 0) {
			RR();
		}
		else if (ui->comboBox->currentIndex() == 1) {
			MLFQ();
		}
	}
	else if (ui->tabWidget->tabBar()->currentIndex() == 1) {
		if (ui->comboBox_2->currentIndex() == 0) {
			FCFS();
		}
		else if (ui->comboBox_2->currentIndex() == 1) {
			SJF();
		}
		else if (ui->comboBox_2->currentIndex() == 2) {
			HRRN();
		}
	}

	if (fin == ris.size()) {
		ui->pushButton_reset->setEnabled(true);
		ui->pushButton_reset_2->setEnabled(true);
		timer->stop();
		return;
	}
}

void Widget::on_pushButton_start_clicked()
{
	ui->pushButton_start->setEnabled(false);

	ui->groupBox_prcs->setEnabled(false);
	ui->groupBox_jb->setEnabled(false);
	ui->pushButton_reset->setEnabled(false);
	ui->pushButton_reset_2->setEnabled(false);
	timer->start(1000);
}

void Widget::RR() {
	if (curTimePiece == 0) {
		int maxx = INF;
		for (int i = 0; i < ris.size(); ++i) {
			if (ris[i].arriveTime <= time && ris[i].priority < maxx) {
				idx = i;
				maxx = ris[i].priority;
			}
		}

		if (idx < 0) {
			ui->listWidget->addItem(new QListWidgetItem(QString("当前没有可执行进程，等待中...")));
			ui->listWidget->scrollToBottom();
			time++;
			return;
		}
		else {
			QString str("【第" + QString::number(time) + "秒】：" + "进程" + QString::number(ris[idx].index) + "开始运行！");
			ui->listWidget->addItem(new QListWidgetItem(QString(str)));
			ui->listWidget->scrollToBottom();
		}
	}

	//运行1s
	//如果是第一次上机，记录开始时间
	if (ris[idx].doneTime == 0) {
		ris[idx].startTime = time;
	}
	QString str("【第" + QString::number(time) + "秒】：" + "进程" + QString::number(ris[idx].index) + "正在运行...");
	ui->listWidget->addItem(new QListWidgetItem(QString(str)));
	ui->listWidget->scrollToBottom();
	ris[idx].doneTime++;
	ris[idx].progressBar->setValue(ris[idx].doneTime);

	time++;
	curTimePiece++;

	//如果执行结束
	if (ris[idx].doneTime == ris[idx].runTime) {
		QString str("【第" + QString::number(time) + "秒】：" + "进程" + QString::number(ris[idx].index) + "完成！");
		ui->listWidget->addItem(new QListWidgetItem(QString(str)));
		ui->listWidget->scrollToBottom();
		Sleep(50);

		ris[idx].finishTime = time;
		ris[idx].turnTime = ris[idx].finishTime - ris[idx].arriveTime;

		int rc = ui->tableWidget_finishedQueue->rowCount();
		ui->tableWidget_finishedQueue->insertRow(rc);
		ui->tableWidget_finishedQueue->setItem(rc, 0, new QTableWidgetItem(QString::number(ris[idx].index)));
		ui->tableWidget_finishedQueue->setItem(rc, 1, new QTableWidgetItem(QString::number(ris[idx].startTime)));
		ui->tableWidget_finishedQueue->setItem(rc, 2, new QTableWidgetItem(QString::number(ris[idx].finishTime)));
		ui->tableWidget_finishedQueue->setItem(rc, 3, new QTableWidgetItem(QString::number(ris[idx].turnTime)));
		for (int j = 0; j < 4; ++j) {
			ui->tableWidget_finishedQueue->item(rc, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
		ui->tableWidget_finishedQueue->scrollToBottom();
		fin++;

		//        int rmv = idx;
		//        ris.erase(ris.begin() + rmv, ris.begin() + rmv + 1);
		ris[idx].priority += INF;
		int rmv = ris[idx].progressBar->parentWidget()->frameGeometry().y() - 1;
		ui->tableWidget_readyQueue->removeRow(rmv);
		idx = -1;

		curTimePiece = 0;
		return;
	}

	if (curTimePiece == timePiece) {
		QString str("【第" + QString::number(time) + "秒】：" + "进程" + QString::number(ris[idx].index) + "运行完时间片，优先级下降！");
		ui->listWidget->addItem(new QListWidgetItem(QString(str)));
		ui->listWidget->scrollToBottom();
		ris[idx].priority += 2;
		curTimePiece = 0;
		return;
	}
}

void Widget::MLFQ() {
	for (int i = 0; i < ris.size(); ++i) {
		if (ris[i].arriveTime <= time && ris[i].currentQueue == 0) {
			ris[i].currentQueue = 1;
			q[1].push(i);
			//que[0].push(ris[i]);
			int chg = ris[i].progressBar->parentWidget()->frameGeometry().y() - 1;
			ui->tableWidget_readyQueue->setItem(chg, 4, new QTableWidgetItem(QString::number(1)));
		}
	}

	bool flag = false;
	for (int i = 1; i <= 3; ++i) {
		if (q[i].size()) {
			flag = true;
			if (idx == -1) {
				idx = q[i].front();
				//idx = que[i].front().index - 1;
			}

			//抢占
			if (ris[idx].currentQueue != i) {
				q[ris[idx].currentQueue].push(idx);
				q[ris[idx].currentQueue].pop();
				idx = q[i].front();
				curTimePiece = 0;
			}


			//执行
			if (curTimePiece == 0) {
				QString str("【第" + QString::number(time) + "秒】：" + "进程" + QString::number(ris[idx].index) + "开始运行！");
				ui->listWidget->addItem(new QListWidgetItem(QString(str)));
				ui->listWidget->scrollToBottom();
			}


			if (ris[idx].doneTime == 0) {
				ris[idx].startTime = time;
			}

			QString str("【第" + QString::number(time) + "秒】：" + "进程" + QString::number(ris[idx].index) + "正在运行...");
			ui->listWidget->addItem(new QListWidgetItem(QString(str)));
			ui->listWidget->scrollToBottom();
			ris[idx].doneTime++;
			ris[idx].progressBar->setValue(ris[idx].doneTime);

			time++;
			curTimePiece++;

			//如果执行结束
			if (ris[idx].doneTime == ris[idx].runTime) {
				QString str("【第" + QString::number(time) + "秒】：" + "进程" + QString::number(ris[idx].index) + "完成！");
				ui->listWidget->addItem(new QListWidgetItem(QString(str)));
				ui->listWidget->scrollToBottom();
				Sleep(50);

				ris[idx].finishTime = time;
				ris[idx].turnTime = ris[idx].finishTime - ris[idx].arriveTime;

				int rc = ui->tableWidget_finishedQueue->rowCount();
				ui->tableWidget_finishedQueue->insertRow(rc);
				ui->tableWidget_finishedQueue->setItem(rc, 0, new QTableWidgetItem(QString::number(ris[idx].index)));
				ui->tableWidget_finishedQueue->setItem(rc, 1, new QTableWidgetItem(QString::number(ris[idx].startTime)));
				ui->tableWidget_finishedQueue->setItem(rc, 2, new QTableWidgetItem(QString::number(ris[idx].finishTime)));
				ui->tableWidget_finishedQueue->setItem(rc, 3, new QTableWidgetItem(QString::number(ris[idx].turnTime)));
				for (int j = 0; j < 4; ++j) {
					ui->tableWidget_finishedQueue->item(rc, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
				}
				ui->tableWidget_finishedQueue->scrollToBottom();
				fin++;

				int x = ris[idx].progressBar->frameGeometry().x();
				int y = ris[idx].progressBar->frameGeometry().y();
				int rmv = ui->tableWidget_readyQueue->indexAt(QPoint(x, y)).row();
				ui->tableWidget_readyQueue->removeRow(rmv);
				q[ris[idx].currentQueue].pop();
				idx = -1;

				curTimePiece = 0;
				return;
			}

			if (curTimePiece == priorities[i - 1]) {
				QString str("【第" + QString::number(time) + "秒】：" + "进程" + QString::number(ris[idx].index) + "运行完时间片，优先级下降！");
				ui->listWidget->addItem(new QListWidgetItem(QString(str)));
				ui->listWidget->scrollToBottom();
				if (ris[idx].currentQueue != 3) {
					ris[idx].currentQueue++;
					q[i + 1].push(idx);
					q[i].pop();
					//que[i + 1].push(ris[idx]);
					//que[i].pop();
				}
				else {
					q[i].push(q[i].front());
					q[i].pop();
				}

				curTimePiece = 0;
				idx = -1;
				return;
			}
			break;
		}
	}

	if (!flag) {
		ui->listWidget->addItem(new QListWidgetItem(QString("【第" + QString::number(time) + "秒】：" + "当前没有可执行进程，等待中...")));
		ui->listWidget->scrollToBottom();
		time++;
		return;
	}
}

void Widget::FCFS() {
	for (int i = 0; i < ris.size(); ++i) {
		if (ris[i].arriveTime <= time && ris[i].currentQueue == 0) {
			ris[i].currentQueue = 1;
			q[0].push(i);
		}
	}

	bool flag = false;
	if (q[0].size()) {
		flag = true;
		int idx = q[0].front();
		QString str;
		if (ris[idx].startTime == 0) {
			ris[idx].startTime = time;
			str.append("【第" + QString::number(time) + "秒】：" + "进程" + QString::number(ris[idx].index) + "开始运行！");
		}
		else {
			str.append("【第" + QString::number(time) + "秒】：" + "进程" + QString::number(ris[idx].index) + "正在运行...");
		}
		ui->listWidget->addItem(new QListWidgetItem(QString(str)));
		ui->listWidget->scrollToBottom();
		ris[idx].doneTime++;
		ris[idx].progressBar->setValue(ris[idx].doneTime);

		time++;

		if (ris[idx].doneTime == ris[idx].runTime) {
			QString str("【第" + QString::number(time) + "秒】：" + "进程" + QString::number(ris[idx].index) + "完成！");
			ui->listWidget->addItem(new QListWidgetItem(QString(str)));
			ui->listWidget->scrollToBottom();
			Sleep(50);

			ris[idx].finishTime = time;
			ris[idx].turnTime = ris[idx].finishTime - ris[idx].arriveTime;

			int rc = ui->tableWidget_finishedQueue->rowCount();
			ui->tableWidget_finishedQueue->insertRow(rc);
			ui->tableWidget_finishedQueue->setItem(rc, 0, new QTableWidgetItem(QString::number(ris[idx].index)));
			ui->tableWidget_finishedQueue->setItem(rc, 1, new QTableWidgetItem(QString::number(ris[idx].startTime)));
			ui->tableWidget_finishedQueue->setItem(rc, 2, new QTableWidgetItem(QString::number(ris[idx].finishTime)));
			ui->tableWidget_finishedQueue->setItem(rc, 3, new QTableWidgetItem(QString::number(ris[idx].turnTime)));
			for (int j = 0; j < 4; ++j) {
				ui->tableWidget_finishedQueue->item(rc, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			}
			ui->tableWidget_finishedQueue->scrollToBottom();

			int x = ris[idx].progressBar->frameGeometry().x();
			int y = ris[idx].progressBar->frameGeometry().y();
			int rmv = ui->tableWidget_readyQueue->indexAt(QPoint(x, y)).row();
			ui->tableWidget_readyQueue->removeRow(rmv);

			fin++;
			q[0].pop();
		}
	}
	if (!flag) {
		ui->listWidget->addItem(new QListWidgetItem(QString("当前没有可执行进程，等待中...")));
		ui->listWidget->scrollToBottom();
		time++;
		return;
	}
}

bool cmp1(RowItem a, RowItem b) {
	return a.runTime < b.runTime;
}

void Widget::SJF() {
	for (int i = 0; i < ris.size(); ++i) {
		if (ris[i].arriveTime <= time && ris[i].currentQueue == 0) {
			ris[i].currentQueue = 1;
			tmp.push_back(ris[i]);
		}
	}

	bool flag = false;
	if (tmp.size()) {
		flag = true;
		sort(tmp.begin(), tmp.end(), cmp1);
		int idx = tmp[0].index - 1;
		QString str;
		if (ris[idx].startTime == 0) {
			ris[idx].startTime = time;
			str.append("【第" + QString::number(time) + "秒】：" + "进程" + QString::number(ris[idx].index) + "开始运行！");
		}
		else {
			str.append("【第" + QString::number(time) + "秒】：" + "进程" + QString::number(ris[idx].index) + "正在运行...");
		}
		ui->listWidget->addItem(new QListWidgetItem(QString(str)));
		ui->listWidget->scrollToBottom();
		ris[idx].doneTime++;
		ris[idx].progressBar->setValue(ris[idx].doneTime);

		time++;

		if (ris[idx].doneTime == ris[idx].runTime) {
			QString str("【第" + QString::number(time) + "秒】：" + "进程" + QString::number(ris[idx].index) + "完成！");
			ui->listWidget->addItem(new QListWidgetItem(QString(str)));
			ui->listWidget->scrollToBottom();
			Sleep(50);

			ris[idx].finishTime = time;
			ris[idx].turnTime = ris[idx].finishTime - ris[idx].arriveTime;

			int rc = ui->tableWidget_finishedQueue->rowCount();
			ui->tableWidget_finishedQueue->insertRow(rc);
			ui->tableWidget_finishedQueue->setItem(rc, 0, new QTableWidgetItem(QString::number(ris[idx].index)));
			ui->tableWidget_finishedQueue->setItem(rc, 1, new QTableWidgetItem(QString::number(ris[idx].startTime)));
			ui->tableWidget_finishedQueue->setItem(rc, 2, new QTableWidgetItem(QString::number(ris[idx].finishTime)));
			ui->tableWidget_finishedQueue->setItem(rc, 3, new QTableWidgetItem(QString::number(ris[idx].turnTime)));
			for (int j = 0; j < 4; ++j) {
				ui->tableWidget_finishedQueue->item(rc, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			}
			ui->tableWidget_finishedQueue->scrollToBottom();

			int x = ris[idx].progressBar->frameGeometry().x();
			int y = ris[idx].progressBar->frameGeometry().y();
			int rmv = ui->tableWidget_readyQueue->indexAt(QPoint(x, y)).row();
			ui->tableWidget_readyQueue->removeRow(rmv);

			for (int i = 0; i < tmp.size(); ++i) {
				if (tmp[i].index - 1 == idx) {
					rmv = i;
					break;
				}
			}
			tmp.erase(tmp.begin() + rmv, tmp.begin() + rmv + 1);

			fin++;
		}
	}
	if (!flag) {
		ui->listWidget->addItem(new QListWidgetItem(QString("当前没有可执行进程，等待中...")));
		ui->listWidget->scrollToBottom();
		time++;
		return;
	}
}

bool cmp2(RowItem a, RowItem b) {
	return a.resp > b.resp;
}

void Widget::HRRN() {
	for (int i = 0; i < ris.size(); ++i) {
		if (ris[i].arriveTime <= time && ris[i].currentQueue == 0) {
			ris[i].currentQueue = 1;
			tmp.push_back(ris[i]);
		}
	}

	bool flag = false;
	if (tmp.size()) {
		flag = true;

		int idx = tmp[0].index - 1;
		QString str;
		if (ris[idx].startTime == 0) {
			ris[idx].startTime = time;
			str.append("【第" + QString::number(time) + "秒】：" + "进程" + QString::number(ris[idx].index) + "开始运行！");
		}
		else {
			str.append("【第" + QString::number(time) + "秒】：" + "进程" + QString::number(ris[idx].index) + "正在运行...");
		}
		ui->listWidget->addItem(new QListWidgetItem(QString(str)));
		ui->listWidget->scrollToBottom();
		ris[idx].doneTime++;
		ris[idx].progressBar->setValue(ris[idx].doneTime);

		time++;

		if (ris[idx].doneTime == ris[idx].runTime) {
			QString str("【第" + QString::number(time) + "秒】：" + "进程" + QString::number(ris[idx].index) + "完成！");
			ui->listWidget->addItem(new QListWidgetItem(QString(str)));
			ui->listWidget->scrollToBottom();
			Sleep(50);

			ris[idx].finishTime = time;
			ris[idx].turnTime = ris[idx].finishTime - ris[idx].arriveTime;

			int rc = ui->tableWidget_finishedQueue->rowCount();
			ui->tableWidget_finishedQueue->insertRow(rc);
			ui->tableWidget_finishedQueue->setItem(rc, 0, new QTableWidgetItem(QString::number(ris[idx].index)));
			ui->tableWidget_finishedQueue->setItem(rc, 1, new QTableWidgetItem(QString::number(ris[idx].startTime)));
			ui->tableWidget_finishedQueue->setItem(rc, 2, new QTableWidgetItem(QString::number(ris[idx].finishTime)));
			ui->tableWidget_finishedQueue->setItem(rc, 3, new QTableWidgetItem(QString::number(ris[idx].turnTime)));
			for (int j = 0; j < 4; ++j) {
				ui->tableWidget_finishedQueue->item(rc, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			}
			ui->tableWidget_finishedQueue->scrollToBottom();

			int x = ris[idx].progressBar->frameGeometry().x();
			int y = ris[idx].progressBar->frameGeometry().y();
			int rmv = ui->tableWidget_readyQueue->indexAt(QPoint(x, y)).row();
			ui->tableWidget_readyQueue->removeRow(rmv);

			for (int i = 0; i < tmp.size(); ++i) {
				if (tmp[i].index - 1 == idx) {
					rmv = i;
					break;
				}
			}
			tmp.erase(tmp.begin() + rmv, tmp.begin() + rmv + 1);

			fin++;
			idx = -1;
			for (int i = 0; i < tmp.size(); ++i) {
				tmp[i].resp = (time - tmp[i].arriveTime + tmp[i].runTime) / tmp[i].runTime;
			}
			sort(tmp.begin(), tmp.end(), cmp2);
		}
	}
	if (!flag) {
		ui->listWidget->addItem(new QListWidgetItem(QString("当前没有可执行进程，等待中...")));
		ui->listWidget->scrollToBottom();
		time++;
		return;
	}
}