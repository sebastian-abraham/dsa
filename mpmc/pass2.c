#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {

    FILE *output, *intermed, *optab, *symtab;

    int operand, start, locctr, mnemonicValue, length=20, inCode, inAdd;
    char label[20], opcode[20], operandString[20], mnemonicCode[20], symlab[20];

    // assing file values
    output = fopen("output.txt", "w");
    intermed = fopen("intermed.txt", "r");
    symtab = fopen("symtab.txt", "r");
    optab = fopen("optab.txt", "r");

    fscanf(intermed, "%s%s%x", label, opcode, &operand);
    
    if(strcmp(opcode, "START") == 0) {
        start = operand;
        locctr = start;
        fprintf(output, "H^%s^%06X^%d\n", label, start, length);
    }
    fprintf(output, "T^%06X^%02d", locctr, length);

    while(strcmp(opcode, "END") != 0) {
        inAdd = 0;
        inCode =0;
        fscanf(intermed, "%X%s%s%s", &locctr, label, opcode, operandString);
        printf(" read %X\t%s\t%s\t%s\n", locctr, label, opcode, operandString);

        operand = -1;
        if (strcmp(opcode, "BYTE") == 0){
            printf("^");
            if(operandString[0] == 'C') {
                for(int i = 2; i < strlen(operandString) - 1; i++) {
                    printf("%X",operandString[i]);
                }
            }
            else if(operandString[0] == 'H') {
                for(int i = 2; i < strlen(operandString) - 1; i++) {
                    printf("%C",operandString[i]);
                }
            }      
        }
        else if (strcmp(opcode, "WORD") == 0){
            mnemonicValue = atoi(operandString);
            operand = locctr;
        }
        else if (strcmp(opcode, "RESB") == 0){
            
        }
        else if (strcmp(opcode, "RESW") == 0){
            
        }
        else if (strcmp(opcode, "_")!= 0){
            rewind(optab);
            while(!feof(optab)) {
                printf("searching for %s in opptab\n", opcode);
                fscanf(optab, "%s%d", mnemonicCode, &mnemonicValue);
                if(strcmp(opcode, mnemonicCode) == 0 ) {
                    inCode = mnemonicValue;
                    printf("hey opcode %s is found in opptab\n", mnemonicCode);
                    if(strcmp(operandString, "_") != 0) {
                        rewind(symtab);
                        while (!feof(symtab)) {
                            fscanf(symtab, "%s%X", symlab, &operand);
                            if(strcmp(operandString, symlab) == 0) {
                                printf("comaprring %s wit %s\n", operandString, symlab);
                                inAdd = operand;
                                printf("found\n");
                                break;
                            }
                        }
                    }
                    break;
                }
                else {
                    inCode = 23;
                }
            }
            printf("machine instruction %02d%04X\n", inCode, inAdd);
            fprintf(output, "^%02d%04X", inCode, inAdd);
        }
       
    }

    fclose(output);
    fclose(intermed);
    fclose(symtab);
    fclose(optab);

}