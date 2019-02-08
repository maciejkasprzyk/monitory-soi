//
// Created by maciek on 12.12.18.
//

#ifndef MONITORY_QUEUE_H
#define MONITORY_QUEUE_H

#define QUEUE_SIZE 20

class queue {
    int t[QUEUE_SIZE];
    int endIndex = 0;
    int begIndex = 0;

public:
    void push(int x);

    int front();

    void pop();
};


#endif //MONITORY_QUEUE_H
