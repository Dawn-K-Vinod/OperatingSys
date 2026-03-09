/*
Input a list of processes, their CPU burst times (integral values), arrival times, and priorities. 
Then simulate FCFS, SRTF, non-preemptive priority (a larger priority number implies a higher priority), and RR (quantum = 3 units)
scheduling algorithms on the process mix, 
determining which algorithm results in the minimum average waiting time (over all processes).
*/

#include <stdio.h>
#include <limits.h>

void display(int k, float PID[k], float AT[k], float BT[k], float PN[k], float CT[k], float TAT[k], float WT[k]) {
	printf("\nPID\tAT\tBT\tPN\tCT\tTAT\tWT\n");
	for (int i=0; i<k; i++) {
		printf("%.2f\t", PID[i]);
		printf("%.2f\t", AT[i]);
		printf("%.2f\t", BT[i]);
		printf("%.2f\t", PN[i]);
		printf("%.2f\t", CT[i]);
		printf("%.2f\t", TAT[i]);
		printf("%.2f\t", WT[i]);
		printf("\n");
	}
}

int main() {
	
	int n;
	printf("Enter the number of processes: ");
	scanf("%d", &n);
	
	float PID[n], AT[n], BT[n], PN[n], CT[n], TAT[n], WT[n];
	
	
	// Reading PID, AT, BT
	printf("\n");
	for (int i=0; i<n; i++) {
		PID[i] = i+1;
		printf("Enter the AT of P%d: ", i+1);
		scanf("%f", &AT[i]);
		printf("Enter the BT of P%d: ", i+1);
		scanf("%f", &BT[i]);
		printf("Enter the Priority of P%d: ", i+1);
		scanf("%f", &PN[i]);
		printf("\n");
	}

///////////////////////////////////////////////////////////////////////////////////////////////////
	// FCFS Process Scheduling
	
	//sorting based on AT
	int temp=0;
	for (int i=0; i<n; i++) {
		for (int j=i+1; j<n; j++) {
			if (AT[j] < AT[i] || 
			(AT[j] == AT[i] && PID[j] < PID[i])) {
				temp = PID[j]; 
				PID[j] = PID[i]; 
				PID[i] = temp;
					
				temp = AT[j]; 
				AT[j] = AT[i]; 
				AT[i] = temp;
					
				temp = BT[j]; 
				BT[j] = BT[i]; 
				BT[i] = temp;
			}
		}
	}
	
	// computing CT, TAT, WT of FCFS
	float FCFS_avg_wt=0;
	
	for (int i=0; i<n; i++) {
		if (i==0 || AT[i] >= CT[i-1]) {
			CT[i] = AT[i] + BT[i];
		}
		else CT[i] = CT[i-1] + BT[i];
	
		TAT[i] = CT[i] - AT[i];
		WT[i] = TAT[i] - BT[i];
		FCFS_avg_wt += WT[i];
	}
	
	// Average Waiting time
	FCFS_avg_wt /= n;
	display(n, PID, AT, BT, PN, CT, TAT, WT);
	printf("\nAverage waiting time (FCFS): %.2f\n", FCFS_avg_wt);
	
	for(int i=0; i<n; i++) {CT[i]=0; TAT[i]=0; WT[i]=0;} // to clear previous data
	
///////////////////////////////////////////////////////////////////////////////////////////////////
	// SJF Process Scheduling
	
	int min_bt = INT_MAX, shortest;
	float SJF_avg_wt=0;
	int time=0, completed=0;

	while (completed < n) {
		min_bt = INT_MAX;
		for (int i=0; i<n; i++) {
			if (BT[i] < min_bt && CT[i] == 0) {
				min_bt = BT[i];
				shortest = i;
			}
		}
		if (AT[shortest] > time)
			CT[shortest] = AT[shortest] + BT[shortest];
		else
			CT[shortest] = time + BT[shortest];
		time = CT[shortest];
		completed++;
		
		TAT[shortest] = CT[shortest] - AT[shortest];
		WT[shortest] = TAT[shortest] - BT[shortest];
		SJF_avg_wt += WT[shortest];
	}
		
	// Average Waiting time
	SJF_avg_wt /= n;
	display(n, PID, AT, BT, PN, CT, TAT, WT);
	printf("\nAverage waiting time (SJF): %.2f\n", SJF_avg_wt);
	
	for(int i=0; i<n; i++) {CT[i]=0; TAT[i]=0; WT[i]=0;} // to clear previous data
	
///////////////////////////////////////////////////////////////////////////////////////////////////
	// Priority Process Scheduling
	
	int max_priority_value = INT_MIN, largest;
	float priority_avg_wt=0;
	
	time=0; completed=0;
	
	while (completed < n) {
		max_priority_value = INT_MIN;
		for (int i=0; i<n; i++) {
			if (PN[i] > max_priority_value && CT[i] == 0) {
				max_priority_value = PN[i];
				largest = i;
			}
		}
		
		if (AT[largest] > time)
			CT[largest] = AT[largest] + BT[largest];
		else
			CT[largest] = time + BT[largest];
		time = CT[largest];
		completed++;
		
		TAT[largest] = CT[largest] - AT[largest];
		WT[largest] = TAT[largest] - BT[largest];
		priority_avg_wt += WT[largest];
	}
		
	// Average Waiting time
	priority_avg_wt /= n;
	display(n, PID, AT, BT, PN, CT, TAT, WT);
	printf("\nAverage waiting time (priority): %.2f\n", priority_avg_wt);
	
	float BT_copy[n];
	for(int i=0; i<n; i++) {CT[i]=0; TAT[i]=0; WT[i]=0; BT_copy[i] = BT[i];} // to clear previous data
	
///////////////////////////////////////////////////////////////////////////////////////////////////
	// Round Robin Process Scheduling
	
	int qt = 3;
	time=0; completed=0;
	float RR_avg_wt=0;
	
	while (completed < n) {
		for (int i=0; i<n; i++) {
			if (BT_copy[i] != 0){
			if(BT_copy[i] > qt)	{
				BT_copy[i] -= qt;
				time += qt;
			}
			else {
				time += BT_copy[i];
				BT_copy[i] = 0;
				completed++;
				CT[i] = time;
				
				TAT[i] = CT[i] - AT[i];
				WT[i] = TAT[i] - BT[i];
				RR_avg_wt += WT[i];
			}
			}
		}
	}
	
	RR_avg_wt /= n;
	display(n, PID, AT, BT, PN, CT, TAT, WT);
	printf("\nAverage waiting time (Round Robin): %.2f\n", RR_avg_wt);
	
	printf("\n\n");
	
	
	return 0;
}



