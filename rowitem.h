#ifndef ROWITEM_H
#define ROWITEM_H

#include <QWidget>
#include <QProgressBar>


class RowItem
{
public:
    RowItem();
    RowItem(int index, int arriveTime, int runTime, int priority, int currentQueue);
    //~RowItem();

    int index;
    int arriveTime;
    int runTime;
    int priority;
    int currentQueue;
    QProgressBar* progressBar;
    int startTime;
    int finishTime;
    int turnTime;

private:


};

#endif // ROWITEM_H
