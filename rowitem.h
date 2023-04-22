#ifndef ROWITEM_H
#define ROWITEM_H

#include <QWidget>
#include <QProgressBar>


class RowItem
{
public:
    RowItem();
    RowItem(RowItem& ri);
    RowItem(int index, int arriveTime, int runTime, int priority = 0);
    int index;
    int arriveTime;
    int runTime;
    int priority;
    QProgressBar progressBar;
    int startTime;
    int finishTime;
    int turnTime;

private:


};

#endif // ROWITEM_H
