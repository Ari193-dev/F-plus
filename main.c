#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_program 65536
#define MAX_STACK 65536
#define MAX_RAM 65536

signed int ram[MAX_RAM];
signed int stack[MAX_STACK];
signed int sp = 0;
unsigned int ip = 0;
signed int program[MAX_program];
signed int opcode;

void compile_file() {
    char user_file[256];
	char new_file[256];
    FILE *input, *output;
    char instruction[128];
    int value;

    printf("File to compile: ");
    scanf("%255s", user_file);
	printf("Compiled file: ");
	scanf("%255s", new_file);
    input = fopen(user_file, "r");
    output = fopen(new_file, "w");
    
    if (input == NULL || output == NULL) {
        printf("Error: Can't open input or create output file\n");
        if (input) fclose(input);
        if (output) fclose(output);
        return;
    }

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
        if (strcmp(ptr, "PUSH") == 0) {
            if (fscanf(input, "%d,", &value) == 1) {
                fprintf(output, "1,%d,\n", value);
            }
        } 
        else if (strcmp(ptr, "POP") == 0)   { fprintf(output, "2,\n"); }
        else if (strcmp(ptr, "ADD") == 0)   { fprintf(output, "3,\n"); }
        else if (strcmp(ptr, "SUB") == 0)   { fprintf(output, "4,\n"); }
        else if (strcmp(ptr, "MUL") == 0)   { fprintf(output, "5,\n"); }
        else if (strcmp(ptr, "DIV") == 0)   { fprintf(output, "6,\n"); }
        else if (strcmp(ptr, "DUP") == 0)   { fprintf(output, "7,\n"); }
        else if (strcmp(ptr, "PRINT_STACK") == 0) { fprintf(output, "8,\n"); }
        else if (strcmp(ptr, "HLT") == 0)   { fprintf(output, "9,\n"); }
        else if (strcmp(ptr, "EXIT") == 0)  { fprintf(output, "10,\n"); }  
        else if (strcmp(ptr, "INPUT") == 0) { fprintf(output, "11,\n"); } 
		else if (strcmp(ptr, "STORE") == 0) { 
            if (fscanf(input, "%d,", &value) == 1) {
                fprintf(output, "12,%d,\n", value); 
            }
        } else if (strcmp(ptr, "LOAD") == 0) { 
            if (fscanf(input, "%d,", &value) == 1) {
                fprintf(output, "13,%d,\n", value); 
            }
        } else if (strcmp(ptr, "PRINT_RAM") == 0) { 
            if (fscanf(input, "%d,", &value) == 1) {
                fprintf(output, "14,%d,\n", value); 
            }
        } 
		else if (strcmp(ptr, "RESET") == 0) { fprintf(output, "15,\n"); }
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

void execute_file() {
    char user_file[256];
    FILE *file;
    sp = 0;
    ip = 0;
    for(int m = 0; m < MAX_program; m++) {
        program[m] = 0;
    }
    printf("File to execute: ");
    scanf("%255s", user_file);
    
    file = fopen(user_file, "r");
    if (file == NULL) {
        printf("Error: file doesn't exist in this folder\n");
        return;
    }
	char header[32];
	if (fscanf(file, "%31s", header) != 1 || strcmp(header, "#Fplus") != 0) {
		printf("Error: Invalid file format. Missing or corrupt #Fplus header.\n");
		fclose(file);
		return;
	}
    int i = 0;
    while(fscanf(file, " %d,", &program[i]) == 1) { 
        i++;
        if (i >= MAX_program) break;
    }
    fclose(file);
	
    while (1) {
        opcode = program[ip];
        
        switch (opcode) {
            case 1: // PUSH
                if (sp >= MAX_STACK) {
                    printf("Error: Stack overflow\n");
                    return;
                }
                stack[sp] = program[ip + 1];
                sp++;
                ip += 2; 
                break;
            case 2: // POP
                if (sp <= 0) {
                    printf("Error: Stack underflow\n");
                    return;
                }
                sp--;
                ip++; 
                break;
            case 3: // ADD
                if (sp < 2) {
                    printf("Error: Insuficient elements\n");
                    return;
                }
                stack[sp - 2] = stack[sp - 2] + stack[sp - 1];
                sp--;
                ip++; 
                break;
            case 4: // SUB
                if (sp < 2) {
                    printf("Error: Insuficient elements\n");
                    return;
                }
                stack[sp - 2] = stack[sp - 2] - stack[sp - 1];
                sp--;
                ip++; 
                break;
            case 5: // MUL
                if (sp < 2) {
                    printf("Error: Insuficient elements\n");
                    return;
                }
                stack[sp - 2] = stack[sp - 2] * stack[sp - 1];
                sp--;
                ip++; 
                break;
            case 6: // DIV
                if (sp < 2) {
                    printf("Error: Insuficient elements\n");
                    return;
                }
                stack[sp - 2] = stack[sp - 2] / stack[sp - 1];
                sp--;
                ip++; 
                break;
            case 7: // DUP
                if (sp <= 0) {
                    printf("Error: Insuficient elements\n");
                    return;
                }
                if (sp >= MAX_STACK) {
                    printf("Error: Stack overflow\n");
                    return;
                }
                stack[sp] = stack[sp - 1];
                sp++;
                ip++;
                break;
            case 8: // PRINT_STACK
                if (sp <= 0) {
                    printf("Error: Insuficient elements\n");
                    return;
                }
                printf("%d\n", stack[sp - 1]);
                ip++;
                break;
            case 9: // HALT
                return;
				break;
            case 10: // EXIT
                exit(0);
				break;
			case 11: // INPUT
                if (sp >= MAX_STACK) { 
                    printf("Error: Stack overflow\n"); 
                    return; 
                }
                int c;
                while ((c = getchar()) != '\n' && c != EOF); 

                if (scanf("%d", &stack[sp]) != 1) {
                    printf("Error: Invalid input\n");
                    return;
                }
                sp++;
                ip++;
                break;
			case 12: // STORE
				if (sp <= 0) {
                    printf("Error: Insuficient elements\n");
                    return;
                }
				ram[program[ip+1]] = stack[sp-1];
				ip += 2;
				sp--;
				break;
			case 13: // LOAD
				if (sp >= MAX_STACK) {
					printf("Error: Stack overflow\n"); 
                    return; 
				}
				stack[sp] = ram[program[ip+1]];
				ip += 2;
				sp++;
				break;
			case 14: // PRINT_RAM
				printf("%d\n", ram[program[ip+1]]);
				ip += 2;
				break;
			case 15: // RESET
				ip = 0;
				break;
            default:
                printf("Error: Unknown opcode\n");
                return;
        }
    }       
}

int main() {
    int option;
	while (1) {
		printf("1. Compile file\n");
		printf("2. Execute file\n");
		printf("3. Clear console\n");
		printf("4. Exit\n");
		printf("> ");
		
		if (scanf("%d", &option) != 1) {
			printf("Invalid input\n");
			return 1;
		}
		
		if (option == 1) {
			compile_file();
		} else if (option == 2) {
			execute_file();
		} else if (option == 3) {
			system("cls");
		} else if (option == 4) {
			exit(0);
		} else {
			printf("Invalid option\n");
		}
	}
    return 0;
}
