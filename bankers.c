/*
Author 		: Dawn K Vinod
Description : Simulation of Banker's Algorithm
*/

/*
Obtain a (deadlock-free) process mix and simulate the banker’s algorithm to
determine a safe execution sequence.
*/

#include <stdio.h>

void display_available(int rc, int A[rc]) {
	printf("\nAVAILABLE [");
	for (int i=0; i<rc; i++) printf("  %d", A[i]);
	printf("  ]\n");
	return;
}

int main() {
	int n;
	
	int completed = 0;
	printf("Enter the number of processes: ");
	scanf("%d", &n);
	
	int resource_count;
	printf("Enter the number of Resource types: ");
	scanf("%d", &resource_count);
	
	int Max_resources[resource_count];
	printf("Enter the max number of resources given for each Resource types: ");
	for (int i=0; i<resource_count; i++) scanf("%d", &Max_resources[i]);	
	
	int ALLOCATED [n][resource_count];
	int MAXIMUM [n][resource_count];
	int NEED [n][resource_count];
	int AVAILABLE [resource_count];
	int c_bit[n];
	
	for (int i=0; i<resource_count; i++) AVAILABLE [i] = Max_resources[i];
	
	for (int k=0; k<n; k++) {
		printf("\nProcess (%d)\n",k+1);
		printf("Enter the number of ALLOCATED resources in each resource type: ");
			for (int i=0; i<resource_count; i++) scanf("%d",&ALLOCATED [k][i]);
		printf("Enter the MAXIMUM number of resources required for process completion in each resource type: ");
			for (int i=0; i<resource_count; i++) scanf("%d",&MAXIMUM [k][i]);
		
		for (int i=0; i<resource_count; i++) {
			NEED[k][i] = MAXIMUM [k][i] - ALLOCATED [k][i];
			AVAILABLE [i] -= ALLOCATED[k][i];
		}
		
		c_bit[k] = 0;
	}
    printf("\n");

    ////////////////// display 	
	printf("\nProcess | ");
	printf("%-*s | ", resource_count*4, "ALLOCATION");
    printf("%-*s | ", resource_count*4, "MAX");
    printf("NEED\n");

	for (int i=0; i<n; i++) {
		printf("P%-6d | ", i+1);
		for (int j=0; j<resource_count; j++) printf("%-4d", ALLOCATED[i][j]); printf(" | ");
		for (int j=0; j<resource_count; j++) printf("%-4d", MAXIMUM[i][j]); printf(" | ");
		for (int j=0; j<resource_count; j++) printf("%-4d", NEED[i][j]);
		printf("\n");
	}
	
    ///////////////// execution starts
    printf("\nProcess Mix:\n");
	int skip;
    int deadlock = 0; // first no deadlock
	while (completed < n) {
        if (deadlock) break;
        deadlock = 1; // Assuming initial deadlock
		for (int i=0; i<n; i++) {
			if (c_bit[i]==1) continue;
			skip = 0;
			
			for (int j=0; j<resource_count; j++) {
				if (NEED[i][j] > AVAILABLE[j]) {
					skip = 1;
					break;
				}
			}
			if (skip) continue;
			
			for (int k=0; k<resource_count; k++) AVAILABLE [k] += ALLOCATED[i][k];
			completed++;
            c_bit[i] = 1;
            deadlock = 0; // since at least one process completion happened, No deadlock until now

            printf("\nP%d completed --> ", i+1);
            display_available(resource_count, AVAILABLE);
		}
	}	
    if (deadlock) 
        printf("\nDeadlock occurs at this point....\nImpossible to obtain a Process Mix with no Deadlocks!\n");
    printf("\n");
    return 0;
}