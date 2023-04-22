#include "rowitem.h"

RowItem::RowItem()
{
    this->arriveTime = 0;
    this->finishTime = 0;
    this->index = 0;
    this->priority = 0;
    this->progressBar = new QProgressBar();
    this->runTime = 0;
    this->startTime = 0;
    this->turnTime = 0;
}

RowItem::RowItem(RowItem &ri) {
    this->arriveTime = ri.arriveTime;
    this->finishTime = ri.finishTime;
    this->index = ri.index;
    this->priority = ri.priority;
    this->progressBar = ri.progressBar;
    this->runTime = ri.runTime;
    this->startTime = ri.startTime;
    this->turnTime = ri.turnTime;
}

RowItem::RowItem(int index, int arriveTime, int runTime, int priority = 0) {
    this->arriveTime = arriveTime;
    this->finishTime = finishTime;
    this->index = index;
    this->priority = priority;
    this->progressBar = new QProgressBar();
    this->runTime = 0;
    this->startTime = 0;
    this->turnTime = 0;
}
