#include "vm.h"   
#include <stdio.h>
#include <string.h>

void decode() {
	
	char label_instruction[128];
    int label_val;
    int byte_counter = 0;
    lp = 0;

    while (fscanf(input, " %[^,],", label_instruction) == 1) {
        char *ptr = label_instruction;
		while (*ptr == ' ' || *ptr == '\n' || *ptr == '\r' || *ptr == '\t') {
            ptr++;
		}
        if (strlen(ptr) == 0) continue;

        if (strcmp(ptr, "LABEL") == 0) {
            if (fscanf(input, "%d,", &label_val) == 1) {
                Label[lp].number = label_val;
                Label[lp].position = byte_counter;
                lp++;
            }
        } 
        else if (strcmp(ptr, "PUSH") == 0 || strcmp(ptr, "STORE") == 0 || 
                 strcmp(ptr, "LOAD") == 0 || strcmp(ptr, "PRINT_RAM") == 0 || 
                 strcmp(ptr, "JMP") == 0 || strcmp(ptr, "JIG") == 0 || 
				 strcmp(ptr, "JIL") == 0 || strcmp(ptr, "JIE") == 0 || 
				 strcmp(ptr, "JIN") == 0)  {
            
            int temp_val;
            fscanf(input, "%d,", &temp_val);
            byte_counter += 2; 
        } else {
            byte_counter++;
        }
    }
	
    rewind(input);
	
    fprintf(output, "#Fplus\n");
    while (fscanf(input, " %[^,],", instruction) == 1) {
        char *ptr = instruction;
        while (*ptr == ' ' || *ptr == '\n' || *ptr == '\r' || *ptr == '\t') {
            ptr++;
        }
        int fin = strlen(ptr) - 1;
        while (fin >= 0 && (ptr[fin] == ' ' || ptr[fin] == '\n' || ptr[fin] == '\r' || ptr[fin] == '\t')) {
            ptr[fin] = '\0';
            fin--;
        }
        if (strlen(ptr) == 0) {
            continue;
        }
		if (strcmp(ptr, "LABEL") == 0) {
            int temp;
            fscanf(input, "%d,", &temp);
            continue; 
        }
        if (strcmp(ptr, "JMP") == 0) {
            if (fscanf(input, "%d,", &value) == 1) {
                int real_position = 0;
                for (int i = 0; i < lp; i++) {
					if (Label[i].number == value) {
						real_position =Label[i].position;
					}
                }
                fprintf(output, "0x10,0x%02X,\n", real_position); 
            }
        }
        else if (strcmp(ptr, "PUSH") == 0) {
            if (fscanf(input, "%d,", &value) == 1) {
                fprintf(output, "0x01,0x%02X,\n", value);
            }
        } 
        else if (strcmp(ptr, "POP") == 0)   { fprintf(output, "0x02,\n"); }
        else if (strcmp(ptr, "ADD") == 0)   { fprintf(output, "0x03,\n"); }
        else if (strcmp(ptr, "SUB") == 0)   { fprintf(output, "0x04,\n"); }
        else if (strcmp(ptr, "MUL") == 0)   { fprintf(output, "0x05,\n"); }
        else if (strcmp(ptr, "DIV") == 0)   { fprintf(output, "0x06,\n"); }
        else if (strcmp(ptr, "DUP") == 0)   { fprintf(output, "0x07,\n"); }
        else if (strcmp(ptr, "PRINT_STACK") == 0) { fprintf(output, "0x08,\n"); }
        else if (strcmp(ptr, "HLT") == 0)   { fprintf(output, "0x09,\n"); }
        else if (strcmp(ptr, "EXIT") == 0)  { fprintf(output, "0x0A,\n"); }  
        else if (strcmp(ptr, "INPUT") == 0) { fprintf(output, "0x0B,\n"); } 
		else if (strcmp(ptr, "STORE") == 0) { 
			if (fscanf(input, "%d,", &value) == 1) {
                fprintf(output, "0x0C,0x%02X,\n", value); 
            }
        } else if (strcmp(ptr, "LOAD") == 0) { 
            if (fscanf(input, "%d,", &value) == 1) {
                fprintf(output, "0x0D,0x%02X,\n", value); 
            }
        } else if (strcmp(ptr, "PRINT_RAM") == 0) { 
            if (fscanf(input, "%d,", &value) == 1) {
                fprintf(output, "0x0E,0x%02X,\n", value); 
            }
        }
		else if (strcmp(ptr, "RESET") == 0) { fprintf(output, "0x0F,\n"); }
		else if (strcmp(ptr, "CMP") == 0) { fprintf(output, "0x11,\n"); } 
		else if (strcmp(ptr, "JIG") == 0) {
            if (fscanf(input, "%d,", &value) == 1) {
                int real_position = 0;
                for (int i = 0; i < lp; i++) {
					if (Label[i].number == value) {
						real_position =Label[i].position;
					}
                }
                fprintf(output, "0x12,0x%02X,\n", real_position); 
            }
        } else if (strcmp(ptr, "JIL") == 0) {
            if (fscanf(input, "%d,", &value) == 1) {
                int real_position = 0;
                for (int i = 0; i < lp; i++) {
					if (Label[i].number == value) {
						real_position =Label[i].position;
					}
                }
                fprintf(output, "0x13,0x%02X,\n", real_position); 
            }
        } else if (strcmp(ptr, "JIE") == 0) {
            if (fscanf(input, "%d,", &value) == 1) {
                int real_position = 0;
                for (int i = 0; i < lp; i++) {
					if (Label[i].number == value) {
						real_position =Label[i].position;
					}
                }
                fprintf(output, "0x14,0x%02X,\n", real_position); 
            }
        } else if (strcmp(ptr, "JIN") == 0) {
            if (fscanf(input, "%d,", &value) == 1) {
                int real_position = 0;
                for (int i = 0; i < lp; i++) {
					if (Label[i].number == value) {
						real_position =Label[i].position;
					}
                }
                fprintf(output, "0x15,0x%02X,\n", real_position); 
            }
        }
        else {
            printf("Error: Unknown instruction '%s' in text file\n", ptr);
            fclose(input);
            fclose(output);
            return;
        }
    }

    fclose(input);
    fclose(output);
    printf("%s created\n", new_file);
}
