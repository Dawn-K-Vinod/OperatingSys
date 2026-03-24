
#define SIZE 10
#define RANGE 5000

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void copy_and_sort(int copy[], int arr[], int len) {
    for (int i=0; i<len; i++) copy[i] = arr[i]; //copy

    int temp;
    for (int i=0; i<len; i++) {
        for (int j=i+1; j<len; j++) {
            if (copy[j]<copy[i]) {
                temp = copy[j];
                copy[j] = copy[i];
                copy[i] = temp;
            }
        }
    }
}

void display_arr(int arr[], int len) {
    printf("[ ");
    for (int i=0; i<len; i++) printf("%d ", arr[i]);
    printf("]\n");
    return;
}

void SSTF(int arr[],int len, int head) {
    int total_ST = 0;
    int Shortest_ST;
    int ST;
    int index_closest;
    
    printf("\nSSTF sequence:\n");
    printf("%d ", head);

    for (int k=0; k<len; k++) {
        Shortest_ST = RANGE;
        for (int i=0; i<len; i++) {
            if (arr[i] == -1) continue;

            ST = abs(head-arr[i]);
            if (ST < Shortest_ST) {
                Shortest_ST = ST;
                index_closest = i;
            }
        }
        head = arr[index_closest];
        arr[index_closest] = -1;
        printf("-> %d ", head);
        total_ST += head;
    }
    printf("\nTotal seek time: %d\n\n", total_ST);
    return;
}

int C_SCAN (int arr[],int len, int head, int index) {
    int total_ST = 0;
    printf("C_SCAN sequence:\n");
    printf("%d ", head);

    for (int i=index; i<len; i++) printf("-> %d ", arr[i]);
    total_ST += RANGE-head;

    printf("-> %d -> %d ", RANGE, 0);
    total_ST += RANGE;

    for (int i=0; i<index; i++) printf("-> %d ", arr[i]);
    total_ST += arr[index-1];
    printf("\nTotal seek time: %d\n\n", total_ST);
}

int LOOK (int arr[],int len, int head, int index) {
    int total_ST = 0;
    int start = arr[0];
    int end = arr[len-1];

    printf("LOOK sequence:\n");
    printf("%d ", head);

    for (int i=index; i<len; i++) printf("-> %d ", arr[i]);
    total_ST += end-head;

    for (int i=index-1; i>=0; i--) printf("-> %d ", arr[i]);
    total_ST += end - start;
    printf("\nTotal seek time: %d\n\n", total_ST);
}

int main(int argc, char *argv[]) {
    int head = strtol(argv[1], NULL, 10);

    int cylinders[SIZE];
    int sorted_arr[SIZE];    

    int rand_num;
    srand(time(NULL));
    int i=0;
    while (i<SIZE) {
        rand_num = rand() % RANGE;
        if (rand_num == head) continue;
        cylinders[i] = rand_num;
        i++;
    }
    printf("\nCylinders:\n");
    display_arr(cylinders, SIZE);
    
    printf("\nSorted:\n");
    copy_and_sort(sorted_arr, cylinders, SIZE);
    display_arr(sorted_arr, SIZE);

    SSTF(sorted_arr, SIZE, head);
    copy_and_sort(sorted_arr, cylinders, SIZE);

    int index;
    for (int i=0; i<SIZE; i++) {
        if (sorted_arr[i] > head) {
            index = i;
            break;
        }
    }

    C_SCAN(sorted_arr, SIZE, head, index);
    LOOK(sorted_arr, SIZE, head, index);

    return 0;
}