#include "vm.h"   
#include <stdio.h>
#include <string.h>

void fetch_compile() {
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
}

void fetch_execute() {
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
    while(fscanf(file, " %i,", &program[i]) == 1) { 
        i++;
        if (i >= MAX_program) break;
    }
    fclose(file);
}
