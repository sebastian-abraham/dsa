#include <stdio.h>

struct process{
	int id;
	int arrival_time;
	int burst_time;
};

void main(){
	int n;
	
	printf("Enter number of processes: ");
	scanf("%d", &n);
	
	struct process processes[100];
	for(int i = 0; i<n; i++){
		printf("Enter id, at, bt of process %d: ", i+1);
		scanf("%d %d %d", &processes[i].id, &processes[i].arrival_time, &processes[i].burst_time);
	}
	
	// sorting
	struct process temp;
	for(int i = 0; i < n-1; i++){
		for(int j = 0; j < n-i-1; j++){
			if (processes[j].arrival_time > processes[j+1].arrival_time){
				temp = processes[j];
				processes[j] = processes[j+1];
				processes[j+1] = temp;
			}
		}	
	}
	
	// table
	int table[n][6];
	int ct = 0;
	printf("\nGantt Chart\n");
	for (int i = 0; i<n; i++){
		printf("%d ", ct);
		
		temp = processes[i];
		
		if (ct < temp.arrival_time){
			i--;
			ct = temp.arrival_time;
			printf("- ");
			continue;
		}
		printf("P%d ", temp.id);
		
		table[i][0] = temp.id;
		table[i][1] = temp.arrival_time;
		table[i][2] = temp.burst_time;
		ct += temp.burst_time;
		table[i][3] = ct;
		table[i][4] = ct - temp.arrival_time; // tat
		table[i][5] = table[i][4] - temp.burst_time; // wt
		
	}
	printf("%d\n\n", ct);
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
0 2 10
1 10 5
2 3 8

*/
