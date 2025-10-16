#include <stdio.h>

struct process{
	int id;
	int arrival_time;
	int burst_time;
	int complete;
};

void main(){
	int n;
	
	printf("Enter number of processes: ");
	scanf("%d", &n);
	
	struct process processes[100];
	for(int i = 0; i<n; i++){
		printf("Enter id, at, bt of process %d: ", i+1);
		scanf("%d %d %d", &processes[i].id, &processes[i].arrival_time, &processes[i].burst_time);
		processes[i].complete = 0;
	}
	
	int table[n][6];
	printf("\nGantt Chart\n0 ");
	int current_time = 0, ctr = 0, last_completed = 0;
	while (ctr < n){

		struct process *readyQ[n];
		int readyIndex = 0;
		for (int j = 0; j < n; j++){
			if (processes[j].arrival_time <= current_time && processes[j].complete == 0){
				readyQ[readyIndex++] = &processes[j];
			}
		}
		
		if (readyIndex == 0) {
			current_time += 1;
		}
		else {
			// finding minimum burst time
			int min = readyQ[0]->burst_time, min_index = 0;
			for (int i = 0; i < readyIndex; i++){
				if (readyQ[i]->burst_time < min){
					min = readyQ[i]->burst_time;
					min_index = i;
				}
			}
			if (last_completed != current_time)
				printf("- %d P%d %d ", current_time, readyQ[min_index]->id, current_time + readyQ[min_index]->burst_time);
			else 
				printf("P%d %d ", readyQ[min_index]->id, current_time + readyQ[min_index]->burst_time);
			
			readyQ[min_index]->complete = 1;
			current_time += readyQ[min_index]->burst_time;
			last_completed = current_time;
			
			table[ctr][0] = readyQ[min_index]->id;
			table[ctr][1] = readyQ[min_index]->arrival_time;
			table[ctr][2] = readyQ[min_index]->burst_time;
			// ct += readyQ[min_index]->burst_time;
			table[ctr][3] = current_time;
			table[ctr][4] = current_time - readyQ[min_index]->arrival_time; // tat
			table[ctr][5] = table[ctr][4] - readyQ[min_index]->burst_time; // wt
			
			ctr ++;
		}	
	}
	printf("\n");

	// printf("%d\n\n", ct);
	printf("ID  AT  BT  CT  TAT WT\n");
	for (int i = 0; i<n; i++){
		for (int j = 0; j < 6; j++){
			printf("%02d  ", table[i][j]);
		}
		printf("\n");
	}
	
	int sum_tat = 0, sum_wt = 0;
	for (int i = 0; i<n; i++){
		sum_tat += table[i][4];
		sum_wt += table[i][5];
	}
	
	printf("\nAverage Turn Around Time: %.2f \n", (float) sum_tat/n);
	printf("Average Wait Time: %.2f \n",(float) sum_wt/n);	
}

/*
3
0 0 10
1 11 8
2 11 5
*/
