#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// all outputting numbers is in hex hence %X

void main() {
    // intialize files
    FILE *input, *intermed, *optab, *symtab;

    // assing file values
    input = fopen("input.txt", "r");
    intermed = fopen("intermed.txt", "w");
    symtab = fopen("symtab.txt", "w");
    int operand, start, locctr, mnemonicValue;
    char label[20], opcode[20], operandString[20], mnemonicCode[20];
    
    //input first line usually start directive
    fscanf(input, "%s%s%d", label, opcode, &operand);
    //print the headings to inter med file
    //if it is a start directive set start and print first line to intermed file
    if(strcmp(opcode, "START") == 0) {
            start = operand;
            locctr = start;
            fprintf(intermed, "%-8s %-8s %-8s %-8X", "", label, opcode, operand);
    }
    // else just set it 0
    else {
        locctr = 0;
    }

    // while the the file ends
    while(!feof(input)){
        //read next  line from input
        fscanf(input, "%s%s%s", label, opcode, operandString);
        //write line to output locctr and the line
        fprintf(intermed, "\n%-8X %-8s %-8s %-8s", locctr, label, opcode, operandString);
        //loctr updation logic
        // if there is a label, add to symtab
        if(strcmp(label, "_")!=0) {
            fprintf(symtab, "%-8s %-8X\n", label, locctr);
        }
        //open optab and scan opcode in optab, if exists add 3 to locctr
        optab = fopen("optab.txt", "r");
        while(!feof(optab)) {
            fscanf(optab, "%s %d", mnemonicCode, &mnemonicValue);
            if(strcmp(opcode, mnemonicCode) ==0 ) {
                locctr += 3;
            }
        }
        fclose(optab);
        // if word add 3
        if(strcmp(opcode, "WORD") == 0) {
            locctr += 3;
        }
        // if BYTE add length of byte - 3 for C''
        else if(strcmp(opcode, "BYTE") == 0) {
            locctr += (strlen(operandString) - 3);
        }
        //if RESB just add the value
        else if(strcmp(opcode, "RESB") == 0) {
            locctr += atoi(operandString);
        }
        //if RESW just add the value time 3
        else if(strcmp(opcode, "RESW") == 0) {
            locctr += atoi(operandString) * 3;
        }
        //if end just output program length as start - locctr
        if(strcmp(opcode, "END") == 0) {
            printf("Program Length = %X\n", (locctr - start));
        }
    }
    // close the files
    fclose(input);
    fclose(intermed);
    fclose(symtab);
}