#include <stdio.h>

#define MAX 25

int main() {
    int blocks[MAX], processes[MAX], allocation[MAX];
    int n, m;

    printf("Enter number of memory blocks: ");
    scanf("%d", &n);
    printf("Enter sizes of %d memory blocks:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &blocks[i]);

    printf("Enter number of processes: ");
    scanf("%d", &m);
    printf("Enter sizes of %d processes:\n", m);
    for (int i = 0; i < m; i++) scanf("%d", &processes[i]);

    // Initialize allocation
    for (int i = 0; i < m; i++) allocation[i] = -1;

    for (int i = 0; i < m; i++) {
        int worstIdx = -1;
        for (int j = 0; j < n; j++) {
            if (blocks[j] >= processes[i]) {
                if (worstIdx == -1 || blocks[j] > blocks[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blocks[worstIdx] -= processes[i];
        }
    }

    printf("\n--- Worst Fit Allocation ---\n");
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
