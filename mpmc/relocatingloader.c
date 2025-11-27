    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void main()
    {
        // Corrected variable declarations (one variable per line or comma-separated)
        // Array sizes have been explicitly defined based on typical usage, 
        // and the typo 'bitmask'/'bitmas k' has been fixed.
        char add[7];
        char length[11];
        char input[11];
        char binary[13];
        char bitmask[13]; // Corrected typo and ensured size is defined
        char relocbit_char; // Renamed to clarify it holds a single character ('0' or '1')
        
        int start;
        int inp; // Appears unused but kept
        int len;
        int i;
        int address;
        // Note: The original code used 'opcode' and 'addr' for reading
        // instruction/address parts; they are kept as integers for now,
        // though typically instruction opcodes and data are read as strings (char arrays).
        int opcode; 
        int addr;
        int actualadd;

        FILE *fp1;
        FILE *fp2;
        
        printf("enter the actual starting address:");
        scanf("%d", &start);
        
        fp1 = fopen("obj.txt", "r");
        fp2 = fopen("reloutput.txt", "w");
        
        // Check if files opened successfully (Good practice)
        if (fp1 == NULL || fp2 == NULL) {
            printf("Error opening files.\n");
            return;
        }
        
        fscanf(fp1, "%s", input);
        
        while (strcmp(input, "E") != 0)
        {
            if (strcmp(input, "H") == 0)
            {
                fscanf(fp1, "%s", add);
                fscanf(fp1, "%s", length);
                fscanf(fp1, "%s", input); // Read the next record type
            }
            
            if (strcmp(input, "T") == 0)
            {
                fscanf(fp1, "%d", address);
                fscanf(fp1, "%s", bitmask);
                
                // Logic correction: address+=start is only for the starting address of the T record
                // The actual address update happens inside the loop.
                int current_address = address + start; 
                
                len = strlen(bitmask);
                
                for (i = 0; i < len; i++)
                {
                    // Note: Reading opcode/addr as an int is likely incorrect for object code
                    fscanf(fp1, "%d", &opcode); 
                    fscanf(fp1, "%d", &addr);
                    
                    // Use relocbit_char to store the character '0' or '1'
                    relocbit_char = bitmask[i]; 
                    
                    if (relocbit_char == '0')
                        actualadd = addr;
                    else
                        // This is the core relocation logic
                        actualadd = addr + start; 

                    // Note: The original code used 'address' which was only the starting address.
                    // It should use the updated address for the current instruction.
                    fprintf(fp2, "%d\t%d%d\n", current_address, opcode, actualadd);
                    
                    // Increment the address counter for the next instruction
                    current_address += 3;
                }
                fscanf(fp1, "%s", input); // Read the next record type
            }
        }
        
        fclose(fp1);
        fclose(fp2);
        printf("FINISHED\nCheck for file reloutput.txt\n");
    }