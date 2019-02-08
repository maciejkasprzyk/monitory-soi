//
// Created by maciek on 12.12.18.
//

#include "queue.h"

void queue::push(int x) {
    t[endIndex] = x;
    endIndex = (endIndex + 1 ) % QUEUE_SIZE;
}

int queue::front() {
    return t[begIndex];
}

void queue::pop() {
    begIndex++;
}
