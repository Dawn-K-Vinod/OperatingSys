/*
Simulate the FIFO, LRU, and optimal page-replacement algorithms as follows: First,
generate a random page-reference string where page numbers range from 0 to 9.
Apply the random page-reference string to each algorithm, and record the number of
page faults incurred by each algorithm. Assume that demand paging is used.
The length of the reference string and the number of page frames (varying from 1 to
7) are to be received as command line arguments.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int pageFaults = 0;

void reset(int pf[], int npf) {
    for (int i=0; i<npf; i++) pf[i] = -1;
    pageFaults = 0;
}

void delete_and_add(int arr[], int index, int value) {
    for (int k=index; k>0; k--) arr[k] = arr[k-1];
    arr[0] = value;
}

void FIFO(int rs[], int len, int pf[], int npf) {
    int index = 0;
    int found;
    for (int i=0; i<len; i++) {
        found = 0;
        for (int j=0; j<npf; j++) if (pf[j] == rs[i]) {found = 1; break;}
        if (!found) {
            pf[index] = rs[i];
            index = (index+1)%npf;
            pageFaults++;
        }
    }
    printf("Number of page faults (FIFO): %d\n", pageFaults);
    return;
}

void LRU (int rs[], int len, int pf[], int npf) {
    int found;
    for (int i=0; i<len; i++) {
        found = -1;
        for (int j=0; j<npf; j++) if (pf[j] == rs[i]) {found = j; break;}
        if (found == -1) {
            delete_and_add(pf, npf-1, rs[i]);
            pageFaults++;
        } 
        else delete_and_add(pf, found, pf[found]);
    }
    printf("Number of page faults (LRU): %d\n", pageFaults);
    return;
}

void Optimal(int rs[], int len, int pf[], int npf) {
    int found;
    int farthest;
    for (int i=0; i<len; i++) {
        found = 0;
        for (int j=0; j<npf; j++) {
            if (pf[j] == rs[i]) {
                found = 1; 
                break;
            }
        }
        
        farthest = -1;
        if (found)
            continue;
        else {

            int x;
            int del_value;
            for (int k=0; k<npf; k++) {
                x=i+1;
                for(; x<len; x++) if (pf[k] == rs[x]) break;
                
                if (x > farthest) farthest = x;

                del_value = rs[farthest];
                
                if (x == len) {
                    del_value = pf[k];
                    break;
                }
            }

            for (int k=0; k<npf; k++) {
                if (pf[k] == del_value) {
                    pf[k] = rs[i];
                    break;
                }
            }            
            pageFaults++;
        }
    }
    printf("Number of page faults (Optimal): %d\n", pageFaults);
    return;
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Only pass Exactly two arguments.\n(Reference String Length and No. of Page Frames).\nProgram Terminated...\n");
        return 0;
    }

    char *end1, *end2;
    long length = strtol(argv[1], &end1, 10);
    long npf = strtol(argv[2], &end2, 10);
    if (*end1 != '\0' || *end2 != '\0') {printf("Wrong Input/Argument!"); return 0;}

    int rs[length];
    int pf[npf];

    srand(time(NULL));
    printf("[ ");
    for (int i=0; i<length; i++) {
       rs[i] = rand() % 10;
       printf("%d ", rs[i]);
    }
    printf("]\n");

    // printf("Enter RS: ");
    // for (int i=0; i<length; i++) scanf("%d", &rs[i]);

    reset(pf, npf);
    FIFO(rs, length, pf, npf);
    reset(pf, npf);
    LRU(rs, length, pf, npf);
    reset(pf, npf);
    Optimal(rs, length, pf, npf);

    return 0;
}