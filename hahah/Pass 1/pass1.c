#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(){
    FILE *input, *optab, *symtab, *intermediate;
    int locctr, start, operand, machineCode;

    char opcode[20], label[20], operandString[20], mnemonicCode[20];

    input = fopen("input.txt", "r");
    symtab = fopen("symtab.txt", "w");
    intermediate = fopen("intermediate.txt", "w");

    fscanf(input, "%s %s %d", label, opcode, &operand);
    printf("\nLOC\tLABEL\tOPCODE\tOPERAND\n\n");
    fprintf(intermediate, "%-8s%-8s%-8s%-8s\n\n", "LOC", "LABEL", "OPCODE", "OPERAND");

    if (strcmp(opcode, "START") == 0) {
        start = operand;
        locctr = start;
        printf("\t%s\t%s\t%x\n", label, opcode, operand);
        fprintf(intermediate, "%-8s%-8s%-8s%-8d\n", "", label, opcode, operand);
    }
    else {
        locctr = 0;
    }

    fscanf(input, "%s %s %s", label, opcode, operandString);

    while (!feof(input)) {
        printf("%X\t%s\t%s\t%s\n", locctr, label, opcode, operandString);
        fprintf(intermediate, "%-8X%-8s%-8s%-8s\n", locctr, label, opcode, operandString);

        if (strcmp(label, "-") != 0) {
            fprintf(symtab, "%X\t%s\n", locctr, label);
        }

        optab = fopen("optab.txt", "r");
        fscanf(optab, "%s%d", mnemonicCode, &machineCode);

        while (!feof(optab)) {
            if (strcmp(opcode, mnemonicCode) == 0) {
                locctr = locctr + 3;
                break;
            }
            fscanf(optab, "%s %d", mnemonicCode, &machineCode);
        }
        fclose(optab);

        if (strcmp(opcode, "WORD") == 0) {
            locctr = locctr + 3;
        }

        else if (strcmp(opcode, "RESW") == 0) {
            operand = atoi(operandString);
            locctr = locctr + (3 * operand);
        }

        else if (strcmp(opcode, "BYTE") == 0) {
            locctr = locctr + strlen(operandString) - 3;
        }
                
        else if (strcmp(opcode,"RESB") == 0){
            operand = atoi(operandString);
            locctr = locctr + operand;
        }
        fscanf(input, "%s %s %s", label, opcode, operandString);
    }
    
    if(strcmp(opcode, "END") == 0){
        printf("\nProgram length = %X\n ", locctr - start);
        fprintf(intermediate, "\nProgram length = %X\n", locctr - start);
    }
    fclose(input);
    fclose(symtab);
    fclose(intermediate);
}


/*
OPTAB FILE:
mnemonic    machineCode
*/

