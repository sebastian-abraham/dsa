#include <stdio.h>

void main() {
    int i, j, n, frames, faults = 0, index = 0;
    
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    int memory[frames];
    for (i = 0; i < frames; i++) {
        memory[i] = -1; 
    }

    for (i = 0; i < n; i++) {
        int found = 0;

        for (j = 0; j < frames; j++) {
            if (memory[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            memory[index] = pages[i];
            index = (index + 1) % frames;
            faults++;
        }

        for (j = 0; j < frames; j++) {
            if (memory[j] != -1)
                printf("%d ", memory[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
}
