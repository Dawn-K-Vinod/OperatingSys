// SSTF, LOOK, C-SCAN
/*
Simulate the SSTF, LOOK, and CSCAN disk-scheduling algorithms as follows:
Your program will service a disk with 5,000 cylinders numbered 0 to 4,999. The
program will generate a random series of 10 cylinder requests and service them
according to each of the algorithms listed earlier. The program will be passed the
initial position of the disk head (as a parameter on the command line) and will
report the total number of head movements required by each algorithm.
*/

#define SIZE 10
#define RANGE 5000

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void sort(int arr[], int len) {
    int temp;
    for (int i=0; i<len; i++) {
        for (int j=i+1; j<len; j++) {
            if (arr[j]<arr[i]) {
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
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
    for (int i=0; i<len;i++) {
        if (arr[i] == head) {
            arr[i] = INT_MAX;
            break;
        }
    }
    int SST;
    int temp;
    int next_head;
    int index = 0;
    
    printf("SSTF sequence: ");
    printf("-> %d ", head);
    for (int k=0; k<len-1; k++) {
        SST = RANGE;
        for (int i=0; i<len; i++) {
            temp = abs(head-arr[i]);
            if (temp < SST) {
                SST = temp;
                next_head = arr[i];
                index = i;
            }
        }
        arr[index] = INT_MAX;
        head = next_head;
        printf("-> %d ", next_head);
        total_ST += head;
    }
    printf("\nTotal seek time: %d\n", total_ST);
    return;
}

int main() {
    int head = 1246;

    int cylinders[SIZE];
    int sorted_arr[SIZE];
    cylinders[0] = sorted_arr[0] = head;
    

    int rand_num;
    for (int i=1; i<SIZE; i++) {
        rand_num = rand() % RANGE;
        cylinders[i] = rand_num;
        sorted_arr[i] = rand_num;
    }
    display_arr(cylinders, SIZE);
    
    sort(sorted_arr, SIZE);
    display_arr(sorted_arr, SIZE);
    /////////////////////////////////////////////////////////

    SSTF(sorted_arr, SIZE, head);


    return 0;
}