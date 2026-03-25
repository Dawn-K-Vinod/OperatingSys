#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid;
    int AT;
    int BT;
    int priority;
    int remaining;
    int CT, TAT, WT;
    int completed;
} Process;

void reset(Process p[], Process Orig[] ,int n) {
    for (int i=0; i<n; i++) {
        p[i] = Orig[i];
        p[i].remaining = Orig[i].BT;
        p[i].completed = 0;
    }
}

void display() {

}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process pOrig[n], pCopy[n];


    printf("Enter the AT, BT and Priority of %d Processes: ", n);
    for (int i=0; i<n; i++) {
        pOrig[i].pid = i+1;
        printf("\nP%d: ", i+1);
        scanf("%d %d %d", pOrig[i].AT, pOrig[i].BT, pOrig[i].priority);
    }

    printf("\n%-3d | %-3d | %-3d | %d", "Pid", "AT", "BT", "Priority");
    for (int i=0; i<n; i++) {
        printf("%-3d | %-3d | %-3d | %-8d\n", pOrig[i].pid, pOrig[i].AT, pOrig[i].BT, pOrig[i].priority);
    }

    reset(pCopy, pOrig, n);
    
    
}
