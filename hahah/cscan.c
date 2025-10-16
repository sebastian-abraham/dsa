#include <stdio.h>
#include <stdlib.h>

void main() {
    int n, head, direction, disk_size;
    int queue[100], seek_sequence[200];
    int total_seek_time = 0, index = 0;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &queue[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the disk size: ");
    scanf("%d", &disk_size);

    printf("Enter direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    queue[n] = head;
    n++;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (queue[j] > queue[j + 1]) {
                int temp = queue[j];
                queue[j] = queue[j + 1];
                queue[j + 1] = temp;
            }
        }
    }

    int head_index = 0;
    for (int i = 0; i < n; i++) {
        if (queue[i] == head) {
            head_index = i;
            break;
        }
    }

    if (direction == 1) {
        for (int i = head_index + 1; i < n; i++) {
            seek_sequence[index++] = queue[i];
        }
        if (queue[n - 1] != disk_size - 1) {
            seek_sequence[index++] = disk_size - 1;
        }
        seek_sequence[index++] = 0;
        for (int i = 0; i < head_index; i++) {
            seek_sequence[index++] = queue[i];
        }
    }
    else {
        for (int i = head_index - 1; i >= 0; i--) {
            seek_sequence[index++] = queue[i];
        }
        if (queue[0] != 0) {
            seek_sequence[index++] = 0;
        }
        seek_sequence[index++] = disk_size - 1;
        for (int i = n - 1; i > head_index; i--) {
            seek_sequence[index++] = queue[i];
        }
    }

    printf("\nOrder of disk access:\n%d", head);
    for (int i = 0; i < index; i++) {
        printf(" -> %d", seek_sequence[i]);
        total_seek_time += abs(head - seek_sequence[i]);
        head = seek_sequence[i];
    }

    printf("\nTotal seek time = %d\n", total_seek_time);
    printf("Average seek time = %.2f\n", (float)total_seek_time / n);
}


/*
7
82 170 43 140 24 16 190
50
200
1
*/