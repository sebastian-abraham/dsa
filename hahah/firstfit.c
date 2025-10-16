#include <stdio.h>

void main() {
    int n, m;

    printf("Enter number of memory blocks: ");
    scanf("%d", &n);

    int blocks[n], flag[n];
    
    printf("Enter sizes of %d memory blocks: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &blocks[i]);
        flag[i] = 0;
    }

    printf("Enter number of processes: ");
    scanf("%d", &m);
    int processes[m], allocation[m];
    
    printf("Enter sizes of %d processes: ", m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &processes[i]);
        allocation[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (flag[j] == 0 && blocks[j] >= processes[i]) {
                allocation[i] = j;
                flag[j] = 1; // block occupied
                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < m; i++) {
        printf("%d\t\t%d\t\t", i + 1, processes[i]);
        if (allocation[i] != -1)
            printf("%d", allocation[i] + 1);
        else
            printf("Not Allocated");
        printf("\n");
    }
}


// 4 20 100 40 200 4 90 50 30 40