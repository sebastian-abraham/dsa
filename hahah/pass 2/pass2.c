#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
    char label[10], opcode[10], operand[10], code[10],
    addr[20], symbl[10], locctr[20], value[20];

    int i, len = 20, slen, start;
    FILE *intermediate, *symtab, *record, *output, *optab;
    
    intermediate = fopen("intermediate.txt", "r");
    symtab = fopen("symtab.txt", "r");
    record = fopen("objcode.txt", "w");
    output = fopen("output.txt", "w");
    optab = fopen("optab.txt", "r");
    
    fscanf(intermediate, "%s%s%s%s", locctr, label, opcode, operand);
    
    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        fprintf(output, "%-8s%-8s%-8s%-8s\n", locctr, label, opcode, operand);
        fprintf(record, "H^%s^00%s^0000%d", label, operand, len);
        fscanf(intermediate, "%s%s%s%s", locctr, label, opcode, operand);
        fprintf(record, "\nT^00%d^%d", atoi(locctr), len);
    }
    
    while (strcmp(opcode, "END") != 0) {
        if (strcmp(opcode, "BYTE") == 0) {
            if (operand[0] == 'C') {
                slen = strlen(operand) - 3;
                fprintf(output, "%-8d%-8s%-8s%-8s", atoi(locctr), label, opcode, operand);
                fprintf(record, "^");
                for (i = 2; i < (slen + 2); i++) {
                    fprintf(output, "%X", operand[i]);
                    fprintf(record, "%X", operand[i]);
                }
                fprintf(output, "\n");
            }
            else if (operand[0] == 'X') {
                slen = strlen(operand) - 3;
                fprintf(output, "%-8d%-8s%-8s%-8s", atoi(locctr), label, opcode, operand);
                fprintf(record, "^");
                for (i = 2; i < (slen + 2); i++) {
                    fprintf(output, "%c", operand[i]);
                    fprintf(record, "%c", operand[i]);
                }
                fprintf(output, "\n");
            }
        }
        else if (strcmp(opcode, "WORD") == 0) {
            fprintf(output, "%-8d%-8s%-8s%-8s0000%s\n", atoi(locctr), label, opcode, operand, operand);
            fprintf(record, "^0000%s", operand);
        }
        else if ((strcmp(opcode, "RESW") == 0) || (strcmp(opcode, "RESB") == 0)) {
            fprintf(output, "%-8d%-8s%-8s%-8s\n", atoi(locctr), label, opcode, operand);
        }
        else {
            fscanf(optab, "%s%s", code, value);
            while (strcmp(code, "END") != 0) {
                if (strcmp(opcode, code) == 0)
                    break;
                fscanf(optab, "%s%s", code, value);
            }
            fscanf(symtab, "%s%s", symbl, addr);
            while (!feof(symtab)) {
                if (strcmp(symbl, operand) == 0)
                    break;
                fscanf(symtab, "%s%s", symbl, addr);
            }
            fprintf(output, "%-8d%-8s%-8s%-8s%d%-6d\n", atoi(locctr), label, opcode, operand, atoi(value), atoi(addr));
            fprintf(record, "^%d%d", atoi(value), atoi(addr));
        }
        rewind(symtab);
        rewind(optab);
        fscanf(intermediate, "%s%s%s%s", locctr, label, opcode, operand);
    }
    
    fprintf(record, "\n");
    if (strcmp(opcode, "END") == 0) {
        fprintf(record, "E^00%d", start);
        fprintf(output, "%-8d%-8s%-8s%-8s\n", atoi(locctr), label, opcode, operand);
    }
    
    printf("Object Program produced\n");
}