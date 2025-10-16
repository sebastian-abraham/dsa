/*
Sejith R Nath
51 CS-B
ROUND ROBIN with Gantt Chart
*/
#include<stdio.h>
#include<limits.h> // For INT_MAX

void main(){
    // --- Variable Declarations ---
    int n, tq;
    int pid[20], at[20], bt[20], rbt[20], ct[20], tat[20], wt[20];
    int q[100], f=0, r=0; // Ready queue
    int inq[20] = {0};    // Flag to check if a process is in the queue
    
    int comp = 0, time = 0; // Completed processes and current time
    float atat = 0, awt = 0;

    // --- Gantt Chart Variables ---
    int gantt_pid[100]; // Stores process ID for each Gantt slice
    int gantt_ct[100];  // Stores completion time for each Gantt slice
    int gantt_count = 0;
    int chart_start_time = 0;

    // --- User Input ---
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for(int i=0; i<n; i++){
        printf("Enter the AT and BT of process %d: ", i);
        scanf("%d%d", &at[i], &bt[i]);
        rbt[i] = bt[i]; // Remaining burst time initialized to burst time
        pid[i] = i;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &tq);

    // --- Initialization ---
    // Find the process with the earliest arrival time to start
    int minat_idx = 0;
    for(int i=1; i<n; i++){
        if(at[i] < at[minat_idx]) {
            minat_idx = i;
        }
    }
    time = at[minat_idx];
    chart_start_time = time; // The chart starts at the first arrival time

    // Add the first process to the ready queue
    q[r++] = minat_idx;
    inq[minat_idx] = 1;

    // --- Main Scheduling Loop ---
    while(comp < n){
        // Handle CPU Idle Time: If queue is empty but processes are remaining
        if(f == r) {
            int next_arrival = INT_MAX;
            // Find the next process that will arrive
            for(int i = 0; i < n; i++) {
                if(rbt[i] > 0 && at[i] < next_arrival) {
                    next_arrival = at[i];
                }
            }
            // If there's a gap, record it as IDLE in the Gantt chart
            if(next_arrival > time) {
                gantt_pid[gantt_count] = -1; // -1 represents IDLE
                gantt_ct[gantt_count] = next_arrival;
                gantt_count++;
                time = next_arrival;
            }
            // Add all processes that have arrived by this new time to the queue
            for(int i = 0; i < n; i++) {
                if(rbt[i] > 0 && at[i] <= time && inq[i] == 0) {
                    q[r++] = i;
                    inq[i] = 1;
                }
            }
            continue; // Go to the next loop iteration to process the new queue
        }

        int ind = q[f++]; // Get process from the front of the queue
        int exec_time = 0;

        // Case 1: Process runs for a full time quantum
        if(rbt[ind] > tq){
            exec_time = tq;
            rbt[ind] -= tq;
            time += tq;
        }
        // Case 2: Process runs for its remaining time and finishes
        else{
            exec_time = rbt[ind];
            time += rbt[ind];
            rbt[ind] = 0;
            
            comp++;
            ct[ind] = time;
            tat[ind] = ct[ind] - at[ind];
            wt[ind] = tat[ind] - bt[ind];
            awt += wt[ind];
            atat += tat[ind];
        }

        // *** Record this execution slice for the Gantt Chart ***
        gantt_pid[gantt_count] = pid[ind];
        gantt_ct[gantt_count] = time;
        gantt_count++;

        // Add any newly arrived processes to the queue
        for(int i=0; i<n; i++){
            if(rbt[i] > 0 && inq[i] == 0 && at[i] <= time){
                q[r++] = i;
                inq[i] = 1;
            }
        }

        // If the current process is not finished, add it to the back of the queue
        if(rbt[ind] > 0){
            q[r++] = ind;
        }
    }

    // --- Output Results ---
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0; i<n; i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    // --- Print Gantt Chart ---
    printf("\n\nGantt Chart:\n\n");
    int last_ct = chart_start_time;

    // 1. Print top bar
    printf(" ");
    for(int i=0; i<gantt_count; i++) {
        int duration = gantt_ct[i] - last_ct;
        for(int j=0; j < duration; j++) printf("--");
        printf(" ");
        last_ct = gantt_ct[i];
    }
    printf("\n|");
    last_ct = chart_start_time;

    // 2. Print process IDs
    for(int i=0; i<gantt_count; i++) {
        int duration = gantt_ct[i] - last_ct;
        for(int j=0; j < duration - 1; j++) printf(" ");
        if(gantt_pid[i] == -1)
            printf("IDLE");
        else
            printf("P%d", gantt_pid[i]);
        for(int j=0; j < duration - (gantt_pid[i] == -1 ? 2 : 1) ; j++) printf(" ");
        printf("|");
        last_ct = gantt_ct[i];
    }
    printf("\n ");
    last_ct = chart_start_time;

    // 3. Print bottom bar
    for(int i=0; i<gantt_count; i++) {
        int duration = gantt_ct[i] - last_ct;
        for(int j=0; j < duration; j++) printf("--");
        printf(" ");
        last_ct = gantt_ct[i];
    }
    printf("\n");

    // 4. Print time stamps
    printf("%d", chart_start_time);
    last_ct = chart_start_time;
    for(int i=0; i<gantt_count; i++) {
        int duration = gantt_ct[i] - last_ct;
        for(int j=0; j < duration * 2; j++) printf(" ");
        
        if (last_ct > 9) printf("\b"); // Backspace to align multi-digit numbers
        
        printf(" %d", gantt_ct[i]);
        last_ct = gantt_ct[i];
    }
    printf("\n\n");

    // --- Print Averages ---
    printf("Average Turnaround Time = %.2f\n", atat/n);
    printf("Average Waiting Time = %.2f\n", awt/n);
}