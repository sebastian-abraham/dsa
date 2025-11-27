#include <stdio.h>

#define size 10

int Q[size];
int f = -1, l = -1;

int pop(){
	int val = Q[f];
	if (f == l){
		f = -1; l = -1;
	}
	else {
		f = (f + 1) % size;
	}
	return val;
}

void push(int v){
	if (f == -1){
		f = 0;
	}
	
	l = (l + 1) % size;
	
	Q[l] = v;

}

void main(){
	int page_fault = 0, frames, n, occupied = 0;
	
	printf("Enter number of frames and page references: ");
	scanf("%d%d", &frames, &n);
	
	for (int i = 0; i<n; i++){
		int page;
		
		printf("Enter page: ");
		scanf("%d", &page);
		
		int flag = 0;
		for (int i = 0; i<occupied; i++){
			if (Q[f+i] == page){
				flag = 1;
				break;
			}
		}
		// miss
		if (flag == 0){
			page_fault++; 
			if (occupied == frames) {
				Q[f] = page;
			}
			else{
				push(page);
				occupied ++;
			}
		}
		
		for (int i = 0; i<frames; i++){
			if (i >= occupied){
				printf("- ");
			}
			else{
				printf("%d ", Q[f+i]);
			}
		}
		printf("\n");
		
	}
	printf("Page Faults = %d\n", page_fault);
	
}
