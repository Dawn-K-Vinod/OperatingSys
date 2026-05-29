
#include <stdio.h>
#define MAX 100

typedef struct {
    int pid;
    int at;
    int bt;
    int rt;
    int priority;

    int ct;
    int tat;
    int wt;

} Process;

void sortByArrival(Process p[], int n) {
    Process temp;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
            else if(p[j].at==p[j+1].at && p[j].pid > p[j+1].pid) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}


void copyProcesses(Process src[], Process dest[], int n) {
    for(int i = 0; i < n; i++) {
        dest[i] = src[i];
        dest[i].rt = src[i].bt;
    }
}

void printTable(Process p[], int n) {
    printf("\n----------------------------------------------------------\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    printf("----------------------------------------------------------\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].priority,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }
}

float averageWT(Process p[], int n) {
    int sum = 0;
    for(int i = 0; i < n; i++)
        sum += p[i].wt;
    return (float)sum / n;
}

void fcfs(Process p[], int n) {
    int time = 0;
    for(int i = 0; i < n; i++) {
        if(time < p[i].at)
            time = p[i].at;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    printf("\n========== FCFS ==========\n");
    printTable(p, n);
    printf("\nAverage Waiting Time = %.2f\n", averageWT(p, n));
}

void srtf(Process p[], int n) {
    int completed = 0;
    int time = 0;
    while(completed < n) {
        int minIndex = -1;
        int minRT = 99999;
        for(int i = 0; i < n; i++) {
            if(p[i].at <= time &&
               p[i].rt > 0 &&
               p[i].rt < minRT) {

                minRT = p[i].rt;
                minIndex = i;
            }
        }

        if(minIndex == -1) {
            time++;
            continue;
        }

        p[minIndex].rt--;
        time++;

        if(p[minIndex].rt == 0) {
            p[minIndex].ct = time;
            p[minIndex].tat = p[minIndex].ct - p[minIndex].at;
            p[minIndex].wt = p[minIndex].tat - p[minIndex].bt;
            completed++;
        }
    }

    printf("\n========== SRTF ==========\n");
    printTable(p, n);
    printf("\nAverage Waiting Time = %.2f\n", averageWT(p, n));
}

void priorityScheduling(Process p[], int n) {
    int completed = 0;
    int time = 0;
    int visited[MAX] = {0};

    while(completed < n) {
        int maxPriority = -99999;
        int index = -1;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time &&
               !visited[i] &&
               p[i].priority > maxPriority) {
                maxPriority = p[i].priority;
                index = i;
            }
        }

        if(index == -1) {
            time++;
            continue;
        }

        time += p[index].bt;

        p[index].ct = time;
        p[index].tat = p[index].ct - p[index].at;
        p[index].wt = p[index].tat - p[index].bt;

        visited[index] = 1;
        completed++;
    }

    printf("\n===== Non-Preemptive Priority =====\n");
    printTable(p, n);
    printf("\nAverage Waiting Time = %.2f\n", averageWT(p, n));
}

void roundRobin(Process p[], int n, int quantum) {
    int completed = 0;
    int time = 0;
    while(completed < n) {
        int executed = 0;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].rt > 0) {
                executed = 1;
                if(p[i].rt > quantum) {

                    time += quantum;
                    p[i].rt -= quantum;
                }
                else {
                    time += p[i].rt;
                    p[i].rt = 0;
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    completed++;
                }
            }
        }
        if(!executed)
            time++;
    }

    printf("\n========== Round Robin ==========\n");
    printTable(p, n);
    printf("\nAverage Waiting Time = %.2f\n", averageWT(p, n));
}

int main() {
    int n;
    Process original[MAX];
    Process temp[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        original[i].pid = i + 1;
        printf("\nProcess P%d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &original[i].at);

        printf("Burst Time: ");
        scanf("%d", &original[i].bt);

        printf("Priority: ");
        scanf("%d", &original[i].priority);

        original[i].rt = original[i].bt;
    }

    float avg[4];

    copyProcesses(original, temp, n);
    sortByArrival(temp, n);
    fcfs(temp, n);
    avg[0] = averageWT(temp, n);

    copyProcesses(original, temp, n);
    srtf(temp, n);
    avg[1] = averageWT(temp, n);

    copyProcesses(original, temp, n);
    priorityScheduling(temp, n);
    avg[2] = averageWT(temp, n);

    copyProcesses(original, temp, n);
    sortByArrival(temp, n);
    roundRobin(temp, n, 3);
    avg[3] = averageWT(temp, n);

    float min = avg[0];
    int best = 0;
    for(int i = 1; i < 4; i++) {
        if(avg[i] < min) {
            min = avg[i];
            best = i;
        }
    }

    printf("\n========================================\n");
    switch(best) {
        case 0:
            printf("Best Algorithm: FCFS\n");
            break;
        case 1:
            printf("Best Algorithm: SRTF\n");
            break;
        case 2:
            printf("Best Algorithm: Priority Scheduling\n");
            break;
        case 3:
            printf("Best Algorithm: Round Robin\n");
            break;
    }
    printf("Minimum Average Waiting Time = %.2f\n", min);
    return 0;
}
