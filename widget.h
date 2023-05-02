#ifndef WIDGET_H
#define WIDGET_H

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <windows.h>
#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <vector>
#include <queue>
#include "rowitem.h"

const int INF = 0x3f3f3f3f;

namespace Ui {
	class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget* parent = 0);
	~Widget();
	void RR();
	void MLFQ();
	void FCFS();
	void SJF();
	void HRRN();

private slots:
	void timeout_slot();

	void on_comboBox_activated(const QString& arg1);

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
	Ui::Widget* ui;
	std::vector<RowItem> ris, tmp;
	int fin;
	int timePiece;
	int priorities[3];
	int curTimePiece;
	int time;
	int idx;
	int maxx;
	QTimer* timer;
	std::queue<int> q[4];
	QString doneStr;
};

#endif // WIDGET_H
