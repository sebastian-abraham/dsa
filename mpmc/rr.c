#include <stdio.h>
#include <string.h> // for memcpy

struct process{
	int id;
	int arrival_time;
	int burst_time;
	int remaining_time;
};

int front = -1;
int last = -1;
struct process *readyQ[100];

void enqueue(struct process *p){
	if (front == -1){
		front = 0;
		last = 0;
	}
	else {
		last = (last + 1) % 100;
	}
	readyQ[last] = p;
}

void dequeue(){
	if (front == last){
		front = -1;
		last = -1;
	}
	else{
		front = (front + 1) % 100;
	}
}

void main(){
	int n, time_quantum;
	
	printf("Enter the time quantum: ");
	scanf("%d", &time_quantum);
	
	printf("Enter number of processes: ");
	scanf("%d", &n);
	
	struct process processes[100];
	for (int i = 0; i<n; i++){
		printf("Enter id, at, bt of process %d: ", i+1);
		scanf("%d %d %d", &processes[i].id, &processes[i].arrival_time, &processes[i].burst_time);
		
		processes[i].remaining_time = processes[i].burst_time;
	}
	
	int current_time = 0, completed = 0, time_remaining = 0;
	struct process *current_process = NULL;
	struct process *process_to_be_enqueued = NULL;
	
	int table[n][6];
	printf("\nGantt Chart\n");
	int r = 0;
	while (completed < n){
		// add process to queue
		for (int j = 0; j < n; j++){
			if (processes[j].arrival_time == current_time){
				enqueue(&processes[j]);
			}
		}
		if (process_to_be_enqueued != NULL){
			enqueue(process_to_be_enqueued);
			process_to_be_enqueued = NULL;
		}

		// start new process
		if (time_remaining == 0){
			if (front == -1){
				printf("%d   ", current_time);
				current_time++;
				continue;
			}
			current_process = readyQ[front];
			dequeue();
			time_remaining = time_quantum;
			printf("%d P%d ", current_time, current_process->id);
			r = current_process->id - 1;
			
			table[r][0] = current_process->id;
			table[r][1] = current_process->arrival_time;
			table[r][2] = current_process->burst_time;
			
		}
		
		// time quantum expired
		if (time_remaining == 1){
			current_process->remaining_time--;
			time_remaining = 0;

			if (current_process->remaining_time == 0){
				completed++;
				
				table[r][3] = current_time + 1;
				table[r][4] = current_time + 1 - current_process->arrival_time; // tat
				table[r][5] = table[r][4] - current_process->burst_time; // wt
			}
			else {
				process_to_be_enqueued = current_process;
			}
		}

		// process completed before time quantum
		else if (current_process->remaining_time == 1){
			completed++;
			current_process->remaining_time = 0;
			time_remaining = 0;
			
			table[r][3] = current_time + 1;
			table[r][4] = current_time + 1 - current_process->arrival_time; // tat
			table[r][5] = table[r][4] - current_process->burst_time; // wt
		}

		// time quantum not expired and process not completed
		else {
			current_process->remaining_time--;
			time_remaining--;
		}
		
		current_time ++;
	}	
	printf("%d\n\n", current_time);
	
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
2
3
1 0 5
2 4 2
3 8 4
*/
