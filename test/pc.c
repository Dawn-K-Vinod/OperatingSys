/*
 * Producer-Consumer Problem using POSIX Semaphores
 * Bounded Buffer | OS Lab - B.Tech CSE Semester 4
 *
 * Compile: gcc producer_consumer.c -o pc -lpthread
 * Run:     ./pc
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE  5      // Bounded buffer capacity
#define NUM_ITEMS    4     // Total items to produce/consume

/* ─── Shared Buffer ─────────────────────────────── */
int buffer[BUFFER_SIZE];
int in  = 0;   // Producer inserts at buffer[in]
int out = 0;   // Consumer removes from buffer[out]

/* ─── Semaphores ────────────────────────────────── */
sem_t empty;   // Counts empty slots  (init = BUFFER_SIZE)
sem_t full;    // Counts filled slots (init = 0)
sem_t mutex;   // Binary semaphore for mutual exclusion

/* ─── Producer Thread ───────────────────────────── */
void *producer(void *arg) {
    int item;
    for (int i = 0; i < NUM_ITEMS; i++) {
        item = rand() % 100 + 1;    // Generate a random item

        sem_wait(&empty);           // Wait if no empty slot
        sem_wait(&mutex);           // Enter critical section

        /* Critical Section: Insert into buffer */
        buffer[in] = item;
        printf("Producer: Inserted item %3d at buffer[%d]\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);           // Exit critical section
        sem_post(&full);            // Signal: one more item available

        sleep(1);                   // Simulate production time
    }
    return NULL;
}

/* ─── Consumer Thread ───────────────────────────── */
void *consumer(void *arg) {
    int item;
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full);            // Wait if no item to consume
        sem_wait(&mutex);           // Enter critical section

        /* Critical Section: Remove from buffer */
        item = buffer[out];
        printf("Consumer: Consumed item  %3d from buffer[%d]\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);           // Exit critical section
        sem_post(&empty);           // Signal: one more slot is free

        sleep(2);                   // Simulate consumption time
    }
    return NULL;
}

/* ─── Main ──────────────────────────────────────── */
int main() {
    pthread_t prod_thread, cons_thread;

    /* Initialize semaphores */
    sem_init(&empty, 0, BUFFER_SIZE);  // All slots empty initially
    sem_init(&full,  0, 0);            // No items in buffer initially
    sem_init(&mutex, 0, 1);            // Mutex starts unlocked

    printf("=== Producer-Consumer Problem (Bounded Buffer = %d) ===\n\n",
           BUFFER_SIZE);

    /* Create threads */
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    /* Wait for both threads to finish */
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    /* Destroy semaphores */
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    printf("\n=== All items produced and consumed. Program complete. ===\n");
    return 0;
}