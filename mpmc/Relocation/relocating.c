#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
	char firstBit[2], bitmask[7], addr[5], opcode[3];
	int start, len, address, actualAddress;

	FILE *inputFile = fopen("input.txt", "r");
	FILE *outputFile = fopen("output.txt", "w");

	printf("Enter the actual starting address: ");
    scanf("%d", &start);

	do {
        fscanf(inputFile,"%s", firstBit);
		if (strcmp(firstBit, "T") == 0) {
			fscanf(inputFile, "%d", &address);
			fscanf(inputFile, "%s", bitmask);

			address += start;
			len = strlen(bitmask);

			for (int i = 0; i < len; i++) {
				fscanf(inputFile, "%2s", opcode);
				fscanf(inputFile, "%s", addr);


				if (bitmask[i] == '0')
					actualAddress = atoi(addr);
				else
					actualAddress = atoi(addr) + start;

				fprintf(outputFile, "%d\t%s%d\n", address, opcode, actualAddress);
				address += 3;
			}
		}

	} while (strcmp(firstBit, "E") != 0);

	fclose(inputFile);
	fclose(outputFile);
}