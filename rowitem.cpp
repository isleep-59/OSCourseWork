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

RowItem::RowItem(int index, int arriveTime, int runTime, int priority, int currentQueue) {
    this->arriveTime = arriveTime;
    this->finishTime = finishTime;
    this->index = index;
    this->priority = priority;
    this->currentQueue = currentQueue;
    this->progressBar = new QProgressBar();
    this->runTime = runTime;
    this->startTime = 0;
    this->turnTime = 0;
}

//RowItem::~RowItem() {
//    delete this->progressBar;
//}
