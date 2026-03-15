/*
Author     : Dawn K Vinod
Description: A simple C program (even though we can do it better) to show the simulation of Producer-Consumer solution.
             This has to be done using the Semaphores "empty", "full", "mutex".
             But since we are using 2 basic functions `produce()` and `consume()` and only one function runs at a time, the "mutex" is not needed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int head = 0, tail = 0; // To mark the FRONT and REAR of the Circular queue `buffer[]`
int empty = BUFFER_SIZE, full = 0;
int item = 0; int count = 0;

// To print the BUFFER contents
void printBuffer() {
    printf("\nBuffer contents: [");
    for (int i = 0; i < count; i++) {
        int index = (head + i) % BUFFER_SIZE;
        printf("%d ", buffer[index]);
    }
    printf("]\n");
}

void produce() {
    if (full == BUFFER_SIZE)
        {printf("Waiting for consumer to consume...\n"); return;} // Buffer is full, cannot produce
    buffer[tail % BUFFER_SIZE] = item;
    tail = (tail + 1) % BUFFER_SIZE;
    full++; empty--;
    count++;
    printf("\nProducer produces: %d", item);
    printBuffer();
}

void consume() {
    if (empty == BUFFER_SIZE)
        {printf("Waiting for producer to produce...\n"); return;} // Buffer is empty, cannot consume
    printf("\nConsumer consumes: %d", buffer[head % BUFFER_SIZE]);
    head = (head + 1) % BUFFER_SIZE;
    empty++; full--;
    count--;
    printBuffer();
}

int main() {
    int NUM_OPERATIONS;
    int random_num;

    printf("Enter number of operations: ");
    scanf("%d", &NUM_OPERATIONS);

    int k = NUM_OPERATIONS;
    srand(time(NULL));
    while (k > 0) {
        item = 100 + (rand() % 101);
        if (item % 2 == 0) // same variable `item` is used for randomness, since the time is already a random number
            produce();
        else
            consume();
        k--;
    }
    return 0;
}
