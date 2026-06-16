#include "vm.h"   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute() {
    while (1) {
        opcode = program[ip];
        switch (opcode) {
            case 0x01: // PUSH
                if (sp >= MAX_STACK) {
                    printf("Error: Stack overflow\n");
                    return;
                }
                stack[sp] = program[ip + 1];
                sp++;
                ip += 2; 
                break;
            case 0x02: // POP
                if (sp <= 0) {
                    printf("Error: Stack underflow\n");
                    return;
                }
                sp--;
                ip++; 
                break;
            case 0x03: // ADD
                if (sp < 2) {
                    printf("Error: Insuficient elements\n");
                    return;
                }
                stack[sp - 2] = stack[sp - 2] + stack[sp - 1];
                sp--;
                ip++; 
                break;
            case 0x04: // SUB
                if (sp < 2) {
                    printf("Error: Insuficient elements\n");
                    return;
                }
                stack[sp - 2] = stack[sp - 2] - stack[sp - 1];
                sp--;
                ip++; 
                break;
            case 0x05: // MUL
                if (sp < 2) {
                    printf("Error: Insuficient elements\n");
                    return;
                }
                stack[sp - 2] = stack[sp - 2] * stack[sp - 1];
                sp--;
                ip++; 
                break;
            case 0x06: // DIV
                if (sp < 2) {
                    printf("Error: Insuficient elements\n");
                    return;
                }
                stack[sp - 2] = stack[sp - 2] / stack[sp - 1];
                sp--;
                ip++; 
                break;
            case 0x07: // DUP
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
            case 0x08: // PRINT_STACK
                if (sp <= 0) {
                    printf("Error: Insuficient elements\n");
                    return;
                }
                printf("%d\n", stack[sp - 1]);
                ip++;
                break;
            case 0x09: // HALT
                return;
				break;
            case 0x0A: // EXIT
                exit(0);
				break;
			case 0x0B: // INPUT
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
			case 0x0C: // STORE
				if (sp <= 0) {
                    printf("Error: Insuficient elements\n");
                    return;
                }
				ram[program[ip+1]] = stack[sp-1];
				ip += 2;
				sp--;
				break;
			case 0x0D: // LOAD
				if (sp >= MAX_STACK) {
					printf("Error: Stack overflow\n"); 
                    return; 
				}
				stack[sp] = ram[program[ip+1]];
				ip += 2;
				sp++;
				break;
			case 0x0E: // PRINT_RAM
				printf("%d\n", ram[program[ip+1]]);
				ip += 2;
				break;
			case 0x0F: // RESET
				ip = 0;
				break;
			case 0x10: // JMP
				ip = program[ip+1];
				break;
			case 0x11: // CMP
				if (stack[sp-2] > stack[sp-1]) {
					AGB = 1;
					ALB = 0;
					AEB = 0;
					ANB = 0;
				} else if (stack[sp-2] < stack[sp-1]) {
					AGB = 0;
					ALB = 1;
					AEB = 0;
					ANB = 0;
				} else if (stack[sp-2] == stack[sp-1]) {
					AGB = 0;
					ALB = 0;
					AEB = 1;
					ANB = 0;
				} else if (stack[sp-2] != stack[sp-1]) {
					AGB = 0;
					ALB = 0;
					AEB = 0;
					ANB = 1;
				}
				ip++;
				break;
			case 0x12: // JIG
				if (AGB == 1) {
					ip = program[ip+1];
				} else {
					ip += 2;
				}
				break;
			case 0x13: // JIL
				if (ALB == 1) {
					ip = program[ip+1];
				} else {
					ip += 2;
				}
				break;
			case 0x14: // JIE
				if (AEB == 1) {
					ip = program[ip+1];
				} else {
					ip += 2;
				}
				break;
			case 0x15: // JIN
				if (ANB == 1) {
					ip = program[ip+1];
				} else {
					ip += 2;
				}
				break;
            default:
                printf("Error: Unknown opcode\n");
                return;
        }
    }       
}
