    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    void main() {
        // initialize variables for file handling and string storage
        char label[10], opcode[10], operand[10], code[10], addr[20], symbl[10], locctr[20], value[20];
        int i, len = 20, slen, start;
        FILE *intermediate, *symtab, *record, *output, *optab;

        // open necessary files for reading input and writing object code
        intermediate = fopen("intermediate.txt", "r");
        symtab = fopen("symtab.txt", "r");
        optab = fopen("optab.txt", "r");
        record = fopen("objcode.txt", "w");
        output = fopen("output.txt", "w");

        // read first line from intermediate file
        fscanf(intermediate, "%s%s%s%s", locctr, label, opcode, operand);

        // if start directive, write header record and first line to output
        if (strcmp(opcode, "START") == 0) {
            start = atoi(operand);
            fprintf(output, "%-8s%-8s%-8s%-8s\n", locctr, label, opcode, operand);
            // write header record H^name^start^length
            fprintf(record, "H^%s^00%s^0000%d", label, operand, len);
            
            // read next line and inistialize first text record
            fscanf(intermediate, "%s%s%%s", locctr, label, opcode, operand);
            fprintf(record, "\nT^00%d^%d", atoi(locctr), len);
        }

        // loop until end of program
        while (strcmp(opcode, "END") != 0) {
            
            // handle byte constants
            if (strcmp(opcode, "BYTE") == 0) {
                // handle character byte constant, convert chars to hex
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
                // handle hex byte constant, write value directly
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
            // if word, write value to object code and listing
            else if (strcmp(opcode, "WORD") == 0) {
                fprintf(output, "%-8d%-8s%-8s%-8s0000%s\n", atoi(locctr), label, opcode, operand, operand);
                fprintf(record, "^0000%s", operand);
            } 
            // if reserve, write to listing but no object code generated
            else if ((strcmp(opcode, "RESW") == 0) || (strcmp(opcode, "RESB") == 0)) {
                fprintf(output, "%-8d%-8s%-8s%-8s\n", atoi(locctr), label, opcode, operand);
            } 
            // handle standard instructions
            else {
                // search optab for opcode value
                fscanf(optab, "%s%s", code, value);
                while (strcmp(code, "END") != 0) {
                    if (strcmp(opcode, code) == 0)
                        break;
                    fscanf(optab, "%s%s", code, value);
                }
                
                // search symtab for operand address
                fscanf(symtab, "%s%s", symbl, addr);
                while (!feof(symtab)) {
                    if (strcmp(symbl, operand) == 0)
                        break;
                    fscanf(symtab, "%s%s", symbl, addr);
                }
                
                // assemble instruction and write to output/object file
                fprintf(output, "%-8d%-8s%-8s%-8s%d%-6d\n", atoi(locctr), label, opcode, operand, atoi(value), atoi(addr));
                fprintf(record, "^%d%d", atoi(value), atoi(addr));
            }

            // reset pointers for optab and symtab lookups
            rewind(symtab);
            rewind(optab);
            
            // read next line from intermediate file
            fscanf(intermediate, "%s%s%s%s", locctr, label, opcode, operand);
        }

        // write new line to finish text record
        fprintf(record, "\n");

        // write end record with start address
        if (strcmp(opcode, "END") == 0) {
            fprintf(record, "E^00%d", start);
            fprintf(output, "%-8d%-8s%-8s%-8s\n", atoi(locctr), label, opcode, operand);
        }
        
        printf("Object Program Generated.\n");
    }