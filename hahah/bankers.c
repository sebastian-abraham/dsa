#include <stdio.h>

void main(){
	int processes, resources;
	
	printf("Enter number of processes: ");
	scanf("%d", &processes);
	
	printf("Enter number of resources: ");
	scanf("%d", &resources);
	
	int max_need[processes][resources],
	remaining_need[processes][resources],
	allocated[processes][resources];
	
	int available[resources], total_instance[resources], completed[processes];
	
	for (int i = 0; i < resources; i++){
		printf("Enter total number of instance for R%d: ", i+1);
		scanf("%d", &total_instance[i]);
	}
	
	for (int i = 0; i < processes; i++){
		printf("Enter allocated resouceses of P%d: ", i+1);
		for (int j = 0; j < resources; j++){
			scanf("%d", &allocated[i][j]);
		}
	}
	
	for (int i = 0; i < processes; i++){
		printf("Enter max need resouceses for P%d: ", i+1);
		for (int j = 0; j < resources; j++){
			scanf("%d", &max_need[i][j]);
		}
	}
	
	// calculate remaining_need
	for (int i = 0; i < processes; i++){
		for (int j = 0; j < resources; j++){
			remaining_need[i][j] = max_need[i][j] - allocated[i][j];
		}
	}
	
	// initialize to 0
	for (int j = 0; j < resources; j++){
		available[j] = 0;
	}
	
	// sum up all allocated resources to available
	for (int i = 0; i < processes; i++){
		for (int j = 0; j < resources; j++){
			available[j] += allocated[i][j];
		}
	}
	
	// sub from total
	for (int j = 0; j < resources; j++){
		available[j] = total_instance[j] - available[j];
	}
	
	// initialize to 0
	for (int j = 0; j < processes; j++){
		completed[j] = 0;
	}
	
	int total_completed = 0,
	total_checked = 0,
	p = 0,
	flag = 0,
	safe_sequence[processes];
	
	while(total_completed < processes){
		// available <= remaining_need
		flag = 0;
		total_checked ++;
		for (int i = 0; i < resources; i++){
			if (remaining_need[p][i] > available[i]){
				flag = 1;
				break;
			}
		}
		// process can be executed
		if (flag == 0 && completed[p] == 0){
			completed[p] = 1;
			safe_sequence[total_completed] = p + 1;
			total_completed ++;
			total_checked = 0;
			
			
			for (int i = 0; i < resources; i++){
				available[i] += allocated[p][i];
			}
		}
		
		p = (p + 1) % processes;
		if (total_checked == processes){
			break;
		}
	}
	
	if (total_completed == processes){
		printf("System is in safe state.\nSafe sequence: ");
		for (int i = 0; i < total_completed - 1; i++){
			printf("P%d -> ", safe_sequence[i]);
		}
		printf("P%d\n", safe_sequence[total_completed - 1]);
	}
	else {
		printf("System is not in safe state.\n");
	}
	
}




/*
5
3
10 5 7

0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

7 5 3
3 2 2
9 0 2
4 2 2
5 3 3

*/
