#include <stdio.h>

struct memoryBlock {
	int size; 
	int p; // process size
}; 

void main() {
	int n; 
	printf("Enter the number of processes: "); 
	scanf("%d", &n);
	
	int p[n]; 
	printf("Enter the %d processes size: ", n); 
	for (int i = 0; i < n; ++i) {
		scanf("%d", &p[i]); 
	}
	
	int b;
	printf("Enter the number of blocks: "); 
	scanf("%d", &b);
	
	struct memoryBlock mem[b]; 
	printf("Enter %d memory size: ", b); 
	for (int i = 0; i < b; ++i) {
		scanf("%d", &mem[i].size); 
		mem[i].p = 0; 
	}
	
	for (int i = 0; i < n; ++i) {
		int avalBlock = -1;
		for (int j = 0; j < b; ++j) {
			if (mem[j].size >= p[i] && mem[j].p == 0) {
                if (avalBlock == -1 || mem[j].size < mem[avalBlock].size) {
                    avalBlock = j;
                }
			}
		}
		
		if (avalBlock != -1) {
			mem[avalBlock].p = p[i];	
		}
	}

    printf("\nMemory Allocation\n"); 
    for (int j = 0; j < b; ++j) {
        if (mem[j].p == 0) {
            printf("%d[] -> ", mem[j].size); 
        } else {
            printf("%d[%d] -> ", mem[j].size, mem[j].p);
        }
    }
    printf("End\n"); 
}














