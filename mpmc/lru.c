#include <stdio.h>

void main() {
    int n, frames, faults = 0;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    int memory[frames];
    int lastUsed[frames];
    
    for (int i = 0; i < frames; i++) {
        memory[i] = -1;
        lastUsed[i] = -1;
    }

    int time = 0; 
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;
        
        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) {
                found = 1;
                lastUsed[j] = time++;
                break;
            }
        }
       
        if (!found) {
            faults++;
            
            int lruIndex = 0;
			int minTime = lastUsed[0];
			for (int k = 1; k < frames; k++) {
				if (lastUsed[k] < minTime) {
					minTime = lastUsed[k];
					lruIndex = k;
				}
			}

            memory[lruIndex] = page;
            lastUsed[lruIndex] = time++;
        }

        for (int j = 0; j < frames; j++) {
            if (memory[j] != -1)
                printf("%d ", memory[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
}

