#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    
    FILE *output, *optab, *symtab, *objcode;
    output = fopen("output.txt", "r");
    optab = fopen("optab.txt", "r");
    symtab = fopen("symtab.txt", "r");
    objcode = fopen("objcode.txt", "w");

    int operand, len=20;
    char label[20], opcode[20];

    fscanf(output, "%s%s%d", label, opcode, &operand);
    fprintf(objcode, "H^%s^00%d^0000%d", label, operand, len);
    printf("H^%s^00%d^0000%d", label, operand, len);

    

    fclose(output);
    fclose(optab);
    fclose(symtab);
    fclose(objcode);

}