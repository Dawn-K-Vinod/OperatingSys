/*
Input a list of processes, their CPU burst times (integral values), arrival times,
and priorities. Then simulate FCFS, SRTF, non-preemptive priority (a larger
priority number implies a higher priority), and RR (quantum = 3 units)
scheduling algorithms on the process mix, determining which algorithm results
in the minimum average waiting time (over all processes).
*/

#include <stdio.h>
#include <limits.h>

float avg_wt;

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

void sort(Process arr[], int n) {
    Process temp;
    for (int i=0; i<n; i++) {
		for (int j=i+1; j<n; j++) {
            if (arr[j].AT < arr[i].AT) {
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
}

void display(Process arr[], int n) {
    printf("\n%-4s | %-3s | %-3s | %-8s | %-3s | %-3s | %s", 
        "Pid", "AT", "BT", "Priority", "CT", "TAT", "WT\n");
    printf("-----+-----+-----+----------+-----+-----+----\n");

    for (int i=0; i<n; i++) {
        printf("P%-3d | %-3d | %-3d | %-8d | %-3d | %-3d | %-3d\n", 
            arr[i].pid, arr[i].AT, arr[i].BT, arr[i].priority, arr[i].CT, arr[i].TAT, arr[i].WT);
    }
}

void FCFS(Process pcopy[], int np) {
    float fcfs_avg_wt = 0;
    int time = 0;

    sort(pcopy, np);
    
    for (int i=0; i<np; i++) {
        if (pcopy[i].AT > time) time = pcopy[i].AT + pcopy[i].BT;
        else time += pcopy[i].BT;

        pcopy[i].CT = time;
        pcopy[i].TAT = pcopy[i].CT - pcopy[i].AT;
        pcopy[i].WT = pcopy[i].TAT - pcopy[i].BT;
        fcfs_avg_wt += pcopy[i].WT;
    }
    fcfs_avg_wt /= np;
    display(pcopy, np);
    printf("\nAverage waiting time (FCFS): %.2f\n", fcfs_avg_wt);
}

void SRTF(Process pcopy[], int np) {
    float srtf_avg_wt = 0;
    int time = 0;
    int completed_count = 0;
    int sRT, sRT_idx;
    int found;

    while (completed_count < np) {
        found = 0;
        sRT = INT_MAX;
        for (int i=0; i<np; i++) {
            if (pcopy[i].completed) continue;
            if (pcopy[i].remaining < sRT && pcopy[i].AT <= time) {
                sRT = pcopy[i].remaining;
                sRT_idx = i;
                found = 1;
            }
        }

        if (!found) { time++; continue; }

        pcopy[sRT_idx].remaining--;
        if (pcopy[sRT_idx].remaining == 0) {
            pcopy[sRT_idx].completed = 1;
            completed_count++;

            pcopy[sRT_idx].CT = time + 1;
            pcopy[sRT_idx].TAT = pcopy[sRT_idx].CT - pcopy[sRT_idx].AT;
            pcopy[sRT_idx].WT = pcopy[sRT_idx].TAT - pcopy[sRT_idx].BT;
            srtf_avg_wt += pcopy[sRT_idx].WT;
        }
        time++;
    }
    srtf_avg_wt /= np;
    display(pcopy, np);
    printf("\nAverage waiting time (SRTF): %.2f\n", srtf_avg_wt);
    avg_wt = srtf_avg_wt;
}

void Priority(Process pcopy[], int np) {
    float priority_avg_wt = 0;
    int time = 0;
    int greatest;
    int g_idx;
    int found;
    
    for (int i=0; i<np; i++) {
        found = 0;
        greatest = INT_MIN;
        for (int j=0; j<np; j++) {
            if (pcopy[j].completed) continue;
            if (pcopy[j].priority > greatest && pcopy[j].AT <= time) {
                greatest = pcopy[j].priority;
                g_idx = j;
                found = 1;
            }
        }
        if (!found) {
            time ++;
            continue;
        }
        pcopy[g_idx].completed = 1;
        time += pcopy[g_idx].BT;
        
        pcopy[g_idx].CT = time;
        pcopy[g_idx].TAT = pcopy[g_idx].CT - pcopy[g_idx].AT;
        pcopy[g_idx].WT = pcopy[g_idx].TAT - pcopy[g_idx].BT;
        priority_avg_wt += pcopy[g_idx].WT;
    }
    priority_avg_wt /= np;
    display(pcopy, np);
    printf("\nAverage waiting time (Priority): %.2f\n", priority_avg_wt);
}

void RoundRobin(Process pcopy[], int np) {
    float rr_avg_wt = 0;
    int qt = 3;
    int time = 0;
    int completed = 0;

    sort(pcopy, np);
    
    while (completed < np) {
        // check if all processes are not yet arrived or done → idle CPU
        int found = 0;
        for (int i = 0; i < np; i++) {
            if (pcopy[i].completed == 0 && pcopy[i].AT <= time) {
                found = 1;
                break;
            }
        }
        if (!found) {
            time++;
            continue;
        }
        
        for (int i=0; i<np; i++) {
            // if process is ready and not finished
            if (pcopy[i].AT <= time && pcopy[i].completed == 0) {
                if (pcopy[i].remaining > qt) {
                    time += qt;
                    pcopy[i].remaining -= qt;
                } 
                else {
                    time += pcopy[i].remaining;
                    pcopy[i].remaining = 0;
                    pcopy[i].completed = 1;
                    
                    pcopy[i].CT = time;
                    pcopy[i].TAT = pcopy[i].CT - pcopy[i].AT;
                    pcopy[i].WT = pcopy[i].TAT - pcopy[i].BT;
                    rr_avg_wt += pcopy[i].WT;
                    completed++;
                }
            }
        }
    }
    rr_avg_wt /= np;
    display(pcopy, np);
    printf("\nAverage waiting time (RoundRobin): %.2f\n", rr_avg_wt);
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

    reset(pCopy, pOrig, n);
    FCFS(pCopy, n);
    reset(pCopy, pOrig, n);
    SRTF(pCopy, n);
    reset(pCopy, pOrig, n);
    Priority(pCopy, n);
    reset(pCopy, pOrig, n);
    RoundRobin(pCopy, n);
    printf("SRTF has the shortest Waiting Time: %.2f\n", avg_wt);
    return 0;
}
