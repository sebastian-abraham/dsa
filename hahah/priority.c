#include <stdio.h>

struct process{
	int id;
	int arrival_time;
	int burst_time;
	int remaining_time;
    int priority; // lower number means higher priority
};

void main(){
	int n;

	printf("Enter number of processes: ");
	scanf("%d", &n);
	
	struct process processes[100];
	for (int i = 0; i<n; i++){
		printf("Enter id, at, bt, priority of process %d: ", i+1);
		scanf("%d %d %d %d", &processes[i].id, &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
		processes[i].remaining_time = processes[i].burst_time;
	}
    
    int current_time = 0, completed = 0;
    struct process *readyQ[100]; // Adjusted to hold struct process
    int readyIndex = 0,
    idle = 0;

    struct process *current_process = NULL;

    int table[n][6], r = 0;
	printf("\nGantt Chart\n");
    while (completed < n){
		// add process to queue

		for (int j = 0; j < n; j++){
			if (processes[j].arrival_time == current_time){
				readyQ[readyIndex++] = &processes[j];
			}
		 }

        for (int i = 0; i < readyIndex - 1; i++) {
            for (int j = 0; j < readyIndex - i - 1; j++) {
                if (readyQ[j]->priority > readyQ[j + 1]->priority) {
                    struct process *temp = readyQ[j];
                    readyQ[j] = readyQ[j + 1];
                    readyQ[j + 1] = temp;
                }
            }
        }

        // Remove processes with remaining_time = 0 from the ready queue
        int newReadyIndex = 0;
        for (int i = 0; i < readyIndex; i++) {
            if (readyQ[i]->remaining_time > 0) {
                readyQ[newReadyIndex++] = readyQ[i];
            }
        }
        readyIndex = newReadyIndex;

        if (readyIndex == 0){
            if (!idle) printf("%d - ", current_time);
            current_time++;
            idle = 1;
            continue;
        }

		// start new process
		if (readyIndex > 0 && (current_process == NULL || current_process != readyQ[0])){
            idle = 0;
            current_process = readyQ[0];
			printf("%d P%d ", current_time, current_process->id);
            // current_process->remaining_time--;

            r = current_process->id - 1;
			
			table[r][0] = current_process->id;
			table[r][1] = current_process->arrival_time;
			table[r][2] = current_process->burst_time;
		}
		
        if (current_process != NULL){
            current_process->remaining_time--;
        }

        if (current_process->remaining_time == 0){
            completed++;

            table[r][3] = current_time + 1;
			table[r][4] = current_time + 1 - current_process->arrival_time; // tat
			table[r][5] = table[r][4] - current_process->burst_time; // wt

            current_process = NULL;
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
4
1 0 1 10
2 3 4 20
3 5 2 30
4 4 1 40

4
1 0 5 10
2 1 4 20
3 2 2 30
4 4 1 30
*/