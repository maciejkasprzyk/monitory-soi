#include <iostream>
#include "monitor.h"
#include "SynchronizedQueue.h"
#include <sys/mman.h>
#include <sys/wait.h>

using namespace std;

#define NUMBER_OF_CHILD_PROCESSES 4

int pids[NUMBER_OF_CHILD_PROCESSES];


void* createSharedMemory(size_t size) {
    // Our memory buffer will be readable and writable:
    int protection = PROT_READ | PROT_WRITE;

    // The buffer will be shared (meaning other processes can access it), but
    // anonymous (meaning third-party processes cannot obtain an address for it),
    // so only this process and its children will be able to use it:
    int visibility = MAP_ANONYMOUS | MAP_SHARED;

    // The remaining parameters to `mmap()` are not important for this use case,
    // but the manpage for `mmap` explains their purpose.

    void* toReturn = mmap(NULL, size, protection, visibility, 0, 0);
    if(toReturn == MAP_FAILED)
    {
        printf("Failed to allocate shared memory.\n");
        exit(EXIT_FAILURE);
    }
    return toReturn;
}


void killAllChilds(int x) {
    for (int i = 0; i < NUMBER_OF_CHILD_PROCESSES; i++) {
        int child = pids[i];
        kill(child, SIGKILL);
    }
}

int main(int argCount, char ** argV){
    if(argCount != 5)
    {
        printf("ILosc elementow ktorą ma przetworzyc:\n(Parzysty producent) (Nieparzysty producent) (Parzysty konsument) (Nieparzysty konsument) \n");
        return 1;
    }

    int evenProducerCounter = atoi(argV[1]);
    int oddProducerCounter = atoi(argV[2]);
    int evenConsumerCounter = atoi(argV[3]);
    int oddConsumerCounter = atoi(argV[4]);



    SynchronizedQueue* pQueue =(SynchronizedQueue*) createSharedMemory(sizeof(SynchronizedQueue));
    SynchronizedQueue qe = SynchronizedQueue();
    memcpy(pQueue, &qe, sizeof(SynchronizedQueue));



    for (int kid = 0; kid < NUMBER_OF_CHILD_PROCESSES; ++kid) {
        int pid = fork();
        if(pid < 0){
            exit(EXIT_FAILURE);
        }

        else if (pid == 0) {
            /* child process */
            switch (kid) {
                case 0: //producer even
                    //printf("START proces nr1\n");
                    while ( evenProducerCounter --){
                        pQueue->produceEven();
                    }
                    break;
                case 1: //producer odd
                    //printf("START proces nr2\n");
                    while (oddProducerCounter-- ){
                        pQueue->produceOdd();
                    }
                    break;
                case 2://consumenr even
                    //printf("START proces nr3\n");
                    while (evenConsumerCounter-- ){
                        pQueue->consumeEven();
                    }
                    break;
                case 3://cosnsumer odd
                    //printf("START proces nr4\n");
                    while ( oddConsumerCounter-- ){
                        pQueue->consumeOdd();
                    }
                    break;
            }
            exit(EXIT_SUCCESS);
        }
        else{
            /*parent process*/
            pids[kid] = pid;
        }
    }
    signal(SIGALRM, killAllChilds);
    alarm(7);

    while(wait(NULL) > 0) {}//wait until all child processes finished

    return 0;

}