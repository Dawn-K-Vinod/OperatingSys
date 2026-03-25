#include <stdio.h>
#include <limits.h>

float avg_wt[4];

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

void display(Process arr[], int n) {
    printf("\n%-3s | %-3s | %-3s | %-8s | %-3s | %-3s | %s", 
        "Pid", "AT", "BT", "Priority", "CT", "TAT", "WT\n");
    for (int i=0; i<n; i++) {
        printf("P%-3d | %-3d | %-3d | %-8d | %-3d | %-3d | %-3d\n", 
            arr[i].pid, arr[i].AT, arr[i].BT, arr[i].priority, arr[i].CT, arr[i].TAT, arr[i].WT);
    }
}

void FCFS(Process pcopy[], int np) {
    float fcfs_avg_wt = 0;
    int completion_time = 0;
    int sv;
    int si;
    
    for (int i=0; i<np; i++) {
        sv = INT_MAX;
        for (int j=0; j<np; j++) {
            if (pcopy[j].completed) continue;
            if (pcopy[j].AT < sv) {
                sv = pcopy[j].AT;
                si = j;
            }
        }
        pcopy[si].completed = 1;
        if (pcopy[si].AT > completion_time) completion_time = pcopy[si].AT + pcopy[si].BT;
        else completion_time += pcopy[si].BT;

        pcopy[si].CT = completion_time;

        pcopy[si].TAT = pcopy[si].CT - pcopy[si].AT;
        pcopy[si].WT = pcopy[si].TAT - pcopy[si].BT;
        fcfs_avg_wt += pcopy[si].WT;
    }
    fcfs_avg_wt /= np;
    display(pcopy, np);
    printf("\nAverage waiting time (FCFS): %.2f\n", fcfs_avg_wt);
}

void SRTF() {

}

void Priority() {

}

void RoundRobin() {

}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process pOrig[n], pCopy[n];


    printf("Enter the AT, BT and Priority of %d Processes: \n", n);
    for (int i=0; i<n; i++) {
        pOrig[i].pid = i+1;
        printf("P%d: ", i+1);
        scanf("%d %d %d", &pOrig[i].AT, &pOrig[i].BT, &pOrig[i].priority);
    }

    printf("\n%-3s | %-3s | %-3s | %s", "Pid", "AT", "BT", "Priority\n");
    for (int i=0; i<n; i++) {
        printf("P%-3d | %-3d | %-3d | %-8d\n", pOrig[i].pid, pOrig[i].AT, pOrig[i].BT, pOrig[i].priority);
    }

    reset(pCopy, pOrig, n);
    FCFS(pCopy, n);
    reset(pCopy, pOrig, n);
    
}
