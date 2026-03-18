
// 10 5 7

#include <stdio.h>

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
		printf("Process (%d)\n",k+1);
		printf("Enter the number of ALLOCATED resources in each resource type: ");
			for (int i=0; i<resource_count; i++) scanf("%d",&ALLOCATED [k][i]);
		printf("Enter the MAXIMUM number of resources required for process completion in each resource type: ");
			for (int i=0; i<resource_count; i++) scanf("%d",&MAXIMUM [k][i]);
		printf("\n");
		
		for (int i=0; i<resource_count; i++) {
			NEED[k][i] = MAXIMUM [k][i] - ALLOCATED [k][i];
			AVAILABLE [i] -= ALLOCATED[k][i];
		}
		
		c_bit[k] = 0;
	}
	
	int skip=0;
	while (completed < n) {
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
		}
	}	
	
	////////////////// display
	printf("\nProcess\tALLOCATION\t\tMAX\t\tNEED\n");
	for (int i=0; i<n; i++) {
		printf("P%d\t", i+1);
		for (int j=0; j<resource_count; j++) printf("%d\t", ALLOCATED[i][j]);
		for (int j=0; j<resource_count; j++) printf("%d\t", MAXIMUM[i][j]);
		for (int j=0; j<resource_count; j++) printf("%d\t", NEED[i][j]);
		printf("\n");
	}
	printf("\n\nAVAILABLE [");
	for (int i=0; i<resource_count; i++) printf("%d\t", AVAILABLE[i]);
	printf("]\n");
	return 0;
}
