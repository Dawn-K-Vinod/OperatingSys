#include <stdio.h>

int main() {
	
	int n;
	printf("Enter the number of processes: ");
	scanf("%d", &n);
	
	float scheduling_table[n][6];
	
	// Reading PID, AT, BT
	for (int i=0; i<n; i++) {
		scheduling_table[i][0] = i+1;
		printf("Enter the AT of P%d: ", i+1);
		scanf("%f", &scheduling_table[i][1]);
		printf("Enter the BT of P-%d: ", i+1);
		scanf("%f", &scheduling_table[i][2]);
	}
	
	//sorting based on AT
	int temp=0;
	for (int i=0; i<n; i++) {
		for (int j=i+1; j<n; j++) {
			if (scheduling_table[j][1] < scheduling_table[i][1]) {
				for (int k=0; k<3; k++) {
					temp = scheduling_table[j][k];
					scheduling_table[j][k] = scheduling_table[i][k];
					scheduling_table[i][k] = temp;
				}
			}
		}
	}
	
	// computing CT, TAT, WT
	float avg_wt=0;
	for (int i=0; i<n; i++) {
		
		scheduling_table[i][3] = scheduling_table[i][1] + scheduling_table[i][2];
	
		
		
		scheduling_table[i][4] = scheduling_table[i][3] - scheduling_table[i][1];
		scheduling_table[i][5] = scheduling_table[i][4] + scheduling_table[i][2];
		avg_wt += scheduling_table[i][5];
	}
	
	// Average Waiting time
	avg_wt /= n;
	
	printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
	for (int i=0; i<n; i++) {
		for (int k=0; k<6; k++) {
			printf("%.2f\t", scheduling_table[i][k]);
		}
		printf("\n");
	}
	printf("\nAverage waiting time (FCFS): %.2f\n", avg_wt);
	
	return 0;
}



