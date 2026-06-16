#ifndef VM_H
#define VM_H
#include <stdio.h>

#define MAX_program 65536
#define MAX_STACK 65536
#define MAX_RAM 65536
#define MAX_LABEL 65536

extern signed int ram[MAX_RAM];
extern signed int stack[MAX_STACK];
extern signed int sp;
extern unsigned int ip;
extern signed int lp;
extern signed int program[MAX_program];
extern signed int opcode;
extern char user_file[256];
extern char new_file[256];
extern FILE *input, *output;
extern char instruction[128];
extern int value;
extern unsigned int AGB;
extern unsigned int ALB;
extern unsigned int AEB;
extern unsigned int ANB;
typedef struct {
    signed int number;
    signed int position;
} label_t;

extern label_t Label[MAX_LABEL];

void fetch_compile();
void fetch_execute();
void decode();
void execute();

#endif   
