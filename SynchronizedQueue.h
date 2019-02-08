//
// Created by maciek on 12.12.18.
//

#ifndef MONITORY_SYNCHRONIZEDQUEUE_H
#define MONITORY_SYNCHRONIZEDQUEUE_H


#include "monitor.h"
#include "queue.h"

using namespace std;

class SynchronizedQueue {
    Monitor monitor;
    Condition produceEvenCondition;
    Condition produceOddCondition;
    Condition consumeEvenCondition;
    Condition consumeOddCondition;
    int nextEvenElementId = 2;
    int nextOddElementId = 1;
    int evenElementsCount = 0;
    int oddElementsCount = 0;
    queue q;

public:
    void produceEven();

    int isEven(int);
    int isOdd(int);
    int canProduceEven();
    int canProduceOdd();
    int canConsumeEven();
    int canConsumeOdd();

    void sendSignalsToWaitingProcesses();

    void produceOdd();

    void consumeEven();

    void consumeOdd();

};


#endif //MONITORY_SYNCHRONIZEDQUEUE_H
