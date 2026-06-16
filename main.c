#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vm.h"

FILE *input = NULL;
FILE *output = NULL;
char user_file[256]; 
char new_file[256];
char instruction[128]; 
int value = 0;
int opcode = 0;
signed int ram[MAX_RAM] = {0};
signed int stack[MAX_STACK] = {0};
int program[MAX_program] = {0};
signed int sp = 0;
unsigned int ip = 0;
signed int lp = 0;
unsigned int AGB = 0;
unsigned int ALB = 0;
unsigned int AEB = 0;
unsigned int ANB = 0;
label_t Label[MAX_LABEL];

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
			fetch_compile();
			decode();
		} else if (option == 2) {
			fetch_execute();
			execute();
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
