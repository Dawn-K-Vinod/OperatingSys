#include <stdio.h>
#include <stdlib.h>

int n=7;

int buffer[7];
int head; int tail;
int empty; int full;
int item;

void produce() {
	if (full==n) return;
	buffer[tail%n]=item; tail=(tail+1)%n;
	full++;
	empty--;
	printf("Producer produces: %d\n", item);
}

void consume() {
	if (empty==0) return;
	printf("Consumer consumes: %d\n", buffer[head%n]);
	head=(head+1)%n;
	empty++;
	full--;
}

int main() {
	int head=0; int tail=0;
	int empty=n; int full=0;

	int k=20;
	int random_num;
	while (k>0) {
		random_num = rand() % 11;
		item = 100 + (rand() % 101);
		if (random_num%2==0) produce();
		else consume();
		k--;
	}
	return 0;
}
