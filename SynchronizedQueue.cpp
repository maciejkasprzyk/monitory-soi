//
// Created by maciek on 12.12.18.
//

#include "SynchronizedQueue.h"

int SynchronizedQueue::isEven(int x) {
    //return  1;
    return (x+1) % 2;
}

int SynchronizedQueue::isOdd(int x) {
    //return 1;
    return (x) % 2;
}

int SynchronizedQueue::canProduceEven(){
    if(evenElementsCount < 10) {
        return 1;
    }
    return 0;
}

int SynchronizedQueue::canProduceOdd() {
    if(oddElementsCount - evenElementsCount < 0) {
        return 1;
    }
    return 0;
}

int SynchronizedQueue::canConsumeEven() {
    if(evenElementsCount + oddElementsCount >= 3 && isEven(q.front())) {
        return  1;
    }
    return 0;
}

int SynchronizedQueue::canConsumeOdd(){
    if(evenElementsCount + oddElementsCount >= 7 && isOdd(q.front())) {
        return  1;
    }
    return 0;
}

void SynchronizedQueue::sendSignalsToWaitingProcesses() {
    if(canConsumeEven()) //wake up even consumer
    {
//        printf("signal 1 warunku\n");
        monitor.signal(consumeEvenCondition);
    }
    if(canConsumeOdd()) //wake up odd consumer
    {
//        printf("signal 2 warunku\n");
        monitor.signal(consumeOddCondition);
    }
    if(canProduceEven()) //wake up even producer
    {
//        printf("signal 3 warunku\n");
        monitor.signal(produceEvenCondition);
    }
    if(canProduceOdd()) // wake up odd producer
    {
//        printf("signal 4 warunku\n");
        monitor.signal(produceOddCondition);
    }
}


void SynchronizedQueue::produceEven() {
//    printf("proces nr 1 probouje wejsc do sekcji krytycznej\n");
    monitor.enter();
//    printf("proces nr 1 wszedl do sekcji krytycznej\n");
    if (!canProduceEven()) {
//        printf("proces nr 1 sprawdza lock warunku\n");
        monitor.wait(produceEvenCondition);
//        printf("proces nr 1 przeszedl lock warunku\n");
    }

//    printf("%d\n", &q);
    printf("1.P %d\n" ,nextEvenElementId);
    q.push(nextEvenElementId);
//    printf("PO POPCHNIECIU na poczatku %d\n", q.front());
    nextEvenElementId = (nextEvenElementId+ 2) % 100;
    evenElementsCount++;

    sendSignalsToWaitingProcesses();
//    printf("proces nr 1 zwalnia sekcje krytyczna\n");
    monitor.leave();
}


void SynchronizedQueue::produceOdd() {
    monitor.enter();
    if (!canProduceOdd()) {
        monitor.wait(produceOddCondition);
    }

    printf("2.P %d\n" , nextOddElementId);
    q.push(nextOddElementId);
    nextOddElementId = (nextOddElementId+2 ) % 100;
    oddElementsCount++;

    sendSignalsToWaitingProcesses();

    monitor.leave();
}

void SynchronizedQueue::consumeEven() {
    monitor.enter();
    if (!canConsumeEven()) {
        monitor.wait(consumeEvenCondition);
    }

    int x = q.front();
    printf("3.C %d\n" , x);
    q.pop();
    evenElementsCount--;

    sendSignalsToWaitingProcesses();

    monitor.leave();
}

void SynchronizedQueue::consumeOdd() {
    monitor.enter();
    if (!canConsumeOdd()) {
        monitor.wait(consumeOddCondition);
    }

    int x = q.front();

    printf("4. C %d\n" ,x);
    q.pop();
    oddElementsCount--;

    sendSignalsToWaitingProcesses();

    monitor.leave();
}


