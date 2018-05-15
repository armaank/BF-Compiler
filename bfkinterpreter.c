// BFK INTERPRETER
// written by armaan kohli 2018


// interprets BrainF*ck programming language into C, then compiles and runs the program

// while this, in effect, does compile BrainF*ck, applying the same methodolgy to other, more complex languages, would be
// idiotic, and probably impossible, since very few other languages have such a simple instruction set and can be so 
// esaily mapped directly into c

#include <stdio.h>

struct instruction
{
	short operator;
	short operand;
};

static struct instruction PROGRAM[4096];
static short STACK[512];
static int SP = 0;

// FUNCTION PROTOTYPE DECLARATIONS

int compile_bf();

int execute_bf();

int main(int argc, const char * argv[])
{
	int status;
	FILE *fp;
	if (argc != 2 || (fp = fopen(argv[1], "r")) == NULL) 
	{
		fprintf(stderr, "usage: %s filename.bf \n", argv[0]);
		return 1;
	}
	status = compile_bf(fp);
	fclose(fp);
	if (status == 0) 
	{	
		printf("compiled successfully \n");
		status = execute_bf();
	}
	if (status == 1) 
	{
		fprintf(stderr, "error \n");
	}
	return status;
}


// 'compiles' bf program by interpreting the instructions line by line and adding it to the instruction struct to be executed in c
int compile_bf(FILE* fp) 
{
	unsigned short pc = 0, jmp_pc;
	int c;
	while ((c = getc(fp)) != EOF && pc < 4096) 
	{
		switch (c) 
		{
			case '>': 
				PROGRAM[pc].operator = 1; 
				break;
			case '<': 
				PROGRAM[pc].operator = 2; 
				break;
			case '+': 
				PROGRAM[pc].operator = 3; 
				break;
			case '-': 
				PROGRAM[pc].operator = 4;
				break;
			case '.': 
				PROGRAM[pc].operator = 5; 
				break;
			case ',': 
				PROGRAM[pc].operator = 6; 
				break;
			case '[': 
				PROGRAM[pc].operator = 7;
				if (SP==512) 
				{
					return 1;
				}
				STACK[SP++] = pc;
				break;
			case ']':
				if (SP==0) 
				{
					return 1;
				}
				jmp_pc = STACK[--SP];
				PROGRAM[pc].operator =  8;
				PROGRAM[pc].operand = jmp_pc;
				PROGRAM[jmp_pc].operand = pc;
				break;
			default: pc--; break;
		}
		pc++;
	}
	if (SP!=0|| pc == 4096) 
	{
		return 1;
	}
	PROGRAM[pc].operator = 0;
	return 0;
}

// reads through the instruction strut PROGRAM and 'executes' the bf instructions, now in c
int execute_bf() 
{
	unsigned short data[65535], pc = 0;
	unsigned int ptr = 65535;
	while (--ptr) 
	{ 
		data[ptr] = 0;
	}
	while (PROGRAM[pc].operator != 0 && ptr < 65535) 
	{
		switch (PROGRAM[pc].operator) 
		{
			case 1:
				ptr++; 
				break;
			case 2: 
				ptr--; 
				break;
			case 3: 
				data[ptr]++; 
				break;
			case 4: 
				data[ptr]--; 
				break;
			case 5: 
				putchar(data[ptr]); 
				break;
			case 6: 
				data[ptr] = (unsigned int)getchar(); 
				break;
			case 7: 
				if(!data[ptr])
				{ 
					pc = PROGRAM[pc].operand; 
				} 
				break;
			case 8: 
				if(data[ptr])
				{ 
					pc = PROGRAM[pc].operand;
				} 
				break;
			default:
				return 1;
		}
	pc++;
	}
	return ptr != 65535 ? 0 : 1;
}




