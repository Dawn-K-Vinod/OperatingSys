#include <stdio.h>
#include <limits.h>

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], rt[n];
    int ct[n], tat[n], wt[n];

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];  // remaining time initially = burst time
    }

    int complete = 0, time = 0, min_rt, shortest;
    int finish_time;
    int is_found;

    while (complete != n) {
        min_rt = INT_MAX;
        is_found = 0;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && rt[i] < min_rt) {
                min_rt = rt[i];
                shortest = i;
                is_found = 1;
            }
        }

        // increment time and repeat the process, if AT is greter than the current time.
        if (!is_found) {
            time++;
            continue;
        }

        rt[shortest]--; // shortest reducing time decremented

        // completion of a process
        if (rt[shortest] == 0) {
            complete++;
            finish_time = time + 1;

            ct[shortest] = finish_time;
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];

            // if (wt[shortest] < 0) wt[shortest] = 0;
        }

        time++;
    }

    float total_wt = 0, total_tat = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);

        total_wt += wt[i];
    }
    printf("\nAverage Waiting Time = %.2f", total_wt/n);
    return 0;
}
