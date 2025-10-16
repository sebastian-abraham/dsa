#include <stdio.h>

#define MAX 25

int main() {
    int blocks[MAX], processes[MAX], allocation[MAX], flag[MAX];
    int n, m;

    printf("Enter number of memory blocks: ");
    scanf("%d", &n);
    printf("Enter sizes of %d memory blocks:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &blocks[i]);
        flag[i] = 0; // 0 means block is free
    }                       
    for (int i = 0; i < m; i++) {
        scanf("%d", &processes[i]);
        allocation[i] = -1; // -1 means not allocated
    }

    // First Fit allocation
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (flag[j] == 0 && blocks[j] >= processes[i]) {
                allocation[i] = j;
                flag[j] = 1; // mark block as used
                break;
            }
        }
    }

    printf("\n--- First Fit Allocation ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < m; i++) {
        printf("%d\t\t%d\t\t", i + 1, processes[i]);
        if (allocation[i] != -1)
            printf("%d", allocation[i] + 1);
        else
            printf("Not Allocated");
        printf("\n");
    }

    return 0;
}

// 4 100 500 200 300 4 212 417 112 426