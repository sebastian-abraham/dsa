#include <stdio.h>
#include <stdlib.h>

void main() {
    int n;
    int queue[100]; 

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk queue sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &queue[i]);
    }

    int head;
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    int total_seek_time = 0;
    printf("\nOrder of disk access:\n");
    printf("%d", head); 

    for (int i = 0; i < n; i++) {
        printf(" -> %d", queue[i]);
        total_seek_time += abs(queue[i] - head);
        head = queue[i];
    }

    printf("\nTotal seek time = %d\n", total_seek_time);
    printf("Average seek time = %.2f\n",(float)total_seek_time / n);
    
}
/*
7
82 170 43 140 24 16 190
*/

