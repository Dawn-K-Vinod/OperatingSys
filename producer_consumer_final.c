#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 7

int buffer[BUFFER_SIZE];
int head = 0, tail = 0;
int empty = BUFFER_SIZE, full = 0;
int item = 0;

void produce() {
    if (full == BUFFER_SIZE)
        return; // Buffer is full, cannot produce
    buffer[tail % BUFFER_SIZE] = item;
    tail = (tail + 1) % BUFFER_SIZE;
    full++;
    empty--;
    printf("Producer produces: %d\n", item);
}

void consume() {
    if (empty == BUFFER_SIZE)
        return; // Buffer is empty, cannot consume
    printf("Consumer consumes: %d\n", buffer[head % BUFFER_SIZE]);
    head = (head + 1) % BUFFER_SIZE;
    empty++;
    full--;
}

int main() {
    int NUM_OPERATIONS;
    int random_num;

    printf("Enter number of operations: ");
    scanf("%d", &NUM_OPERATIONS);

    int k = NUM_OPERATIONS;
    while (k > 0) {
        random_num = rand() % 11;
        item = 100 + (rand() % 101);
        if (random_num % 2 == 0)
            produce();
        else
            consume();
        k--;
    }
    return 0;
}