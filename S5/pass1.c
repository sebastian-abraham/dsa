#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    FILE *input, *output, *symtab, *optab;

    char label[20], opcode[20], operandString[20], mnemonicCode[20];
    int operand, start, locctr, machineCode;
    
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    symtab = fopen("symtab.txt", "w");
    
    fscanf(input, "%s%s%d", label, opcode, &operand);
    fprintf(output,"\nLOC\tLABEL\tOPCODE\tOPERAND\n\n");
    printf("\nLOC\tLABEL\tOPCODE\tOPERAND\n\n");

    if(strcmp(opcode, "START") == 0 ) {
        start = operand;
        locctr = start;
        fprintf(output, "%-8s%-8s%-8s%-8d\n", "", label, opcode, operand);
        printf("%-8s%-8s%-8s%-8d\n", "", label, opcode, operand);
    }
    else {
        locctr = 0;
    }

    fscanf(input, "%s%s%s", label, opcode, operandString);
    while(!feof(input)) {
        fprintf(output, "%-8X%-8s%-8s%-8s\n", locctr, label, opcode, operandString);
        printf("%-8X%-8s%-8s%-8s\n", locctr, label, opcode, operandString);

        if(strcmp("-", label) != 0) {
            fprintf(symtab, "%X\t%s\n", locctr, label);
        }

        optab = fopen("optab.txt", "r");
        fscanf(optab, "%s%d", mnemonicCode, &machineCode);

        while(!feof(optab)) {
            if(strcmp(mnemonicCode, opcode) == 0) {
                locctr += 3;
                break;
            }
            fscanf(optab, "%s%d", mnemonicCode, &machineCode);
        }
        fclose(optab);

        if(strcmp(opcode, "WORD") == 0) {
            locctr +=3;
        }
        else if(strcmp(opcode, "RESW") ==0) {
            locctr += (3 * atoi(operandString));
        }
        else if(strcmp(opcode, "RESB") == 0) {
            locctr += atoi(operandString);
        }
        else if(strcmp(opcode, "BYTE") == 0) {
            locctr += strlen(operandString) - 3;
        }
        fscanf(input, "%s%s%s", label, opcode, operandString);
    }
    if(strcmp(opcode, "END") == 0 ) {
        fprintf(output, "\nProgram Length = %X\n", locctr - start);
        printf("\nProgram Length = %X\n", locctr - start);
    }
    fclose(input);
    fclose(output);
    fclose(symtab);

}