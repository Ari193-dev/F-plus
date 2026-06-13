#include <stdio.h>
#include <stdlib.h>

#define MAX_program 65536
#define MAX_STACK 65536
signed int stack[MAX_STACK];
signed int sp = 0;
unsigned int ip = 0;
signed int program[MAX_program];
signed int opcode;

int main() {
	#pragma region file
    char user_file[256];
    FILE *file;
    for(int m = 0; m < MAX_program; m++) {
        program[m] = 0;
    }

    printf("file: ");
    scanf("%255s", user_file);
    
    file = fopen(user_file, "r");
    if (file == NULL) {
        printf("Error: file doesn't exist in this folder\n");
        exit(1);
    }
    int i = 0;
    while(fscanf(file, "%d,", &program[i]) == 1) { 
        i++;
        if (i >= MAX_program) break;
    }
    fclose(file);
	#pragma endregion
    
	while (1) {
        opcode = program[ip];
        
        switch (opcode) {
            case 1: // PUSH
                if (sp >= MAX_STACK) {
                    printf("Error: Stack overflow\n");
                    exit(2);
                }
                stack[sp] = program[ip + 1];
                sp++;
                ip += 2; 
                break;
            case 2: // POP
                if (sp <= 0) {
                    printf("Error: Stack underflow\n");
                    exit(2);
                }
                sp--;
                ip++; 
                break;
            case 3: // ADD
                if (sp < 2) {
                    printf("Error: Insuficient elements\n");
                    exit(2);
                }
                stack[sp - 2] = stack[sp - 2] + stack[sp - 1];
                sp--;
                ip++; 
                break;
            case 4: // SUB
                if (sp < 2) {
                    printf("Error: Insuficient elements\n");
                    exit(2);
                }
                stack[sp - 2] = stack[sp - 2] - stack[sp - 1];
                sp--;
                ip++; 
                break;
            case 5: // MUL
                if (sp < 2) {
                    printf("Error: Insuficient elements\n");
                    exit(2);
                }
                stack[sp - 2] = stack[sp - 2] * stack[sp - 1];
                sp--;
                ip++; 
                break;
            case 6: // DIV
                if (sp < 2) {
                    printf("Error: Insuficient elements\n");
                    exit(2);
                }
                stack[sp - 2] = stack[sp - 2] / stack[sp - 1];
                sp--;
                ip++; 
                break;
            case 7: // DUP
                if (sp <= 0) {
                    printf("Error: Insuficient elements\n");
                    exit(2);
                }
                if (sp >= MAX_STACK) {
                    printf("Error: Stack overflow\n");
                    exit(2);
                }
                stack[sp] = stack[sp - 1];
                sp++;
                ip++;
                break;
            case 8: // PRINT
                if (sp <= 0) {
                    printf("Error: Insuficient elements\n");
                    exit(2);
                }
                printf("%d\n", stack[sp - 1]);
                ip++;
                break;
			case 9: // HLT
				while(1);
				break;
            case 10: // EXIT
                exit(0);
            default:
                printf("Error: Unknown opcode\n");
                exit(3);
        }
    }       
}
