#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 7
#define NUM_OPERATIONS 20

int buffer[BUFFER_SIZE];
int head = 0;
int tail = 0;
int count = 0; // Number of items in the buffer

// Returns 1 if item was produced, 0 if buffer is full
int produce(int item) {
    if (count == BUFFER_SIZE) {
        printf("Buffer is full. Producer cannot produce.\n");
        return 0;
    }
    buffer[tail] = item;
    tail = (tail + 1) % BUFFER_SIZE;
    count++;
    printf("Producer produces: %d\n", item);
    return 1;
}

// Returns 1 if item was consumed, 0 if buffer is empty
int consume() {
    if (count == 0) {
        printf("Buffer is empty. Consumer cannot consume.\n");
        return 0;
    }
    int item = buffer[head];
    head = (head + 1) % BUFFER_SIZE;
    count--;
    printf("Consumer consumes: %d\n", item);
    return 1;
}

void printBuffer() {
    printf("Buffer contents: ");
    for (int i = 0; i < count; i++) {
        int index = (head + i) % BUFFER_SIZE;
        printf("%d ", buffer[index]);
    }
    printf("\n");
}

int main() {
    int k = NUM_OPERATIONS;
    while (k > 0) {
        int random_num = rand() % 11;
        if (random_num % 2 == 0) {
            int item = 100 + (rand() % 101); // produce random item in [100,200]
            produce(item);
        } else {
            consume();
        }
        printBuffer();
        k--;
    }
    return 0;
}