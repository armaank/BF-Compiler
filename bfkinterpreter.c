#include <stdio.h>

struct instruction 
{
	short operator;
	short operand;
};

struct instruction program[4096]; 
short stack[512];
int sp = 0;

int compile(FILE *fileptr)
{



}

int execute()
{



}

int main(int argc, char *argv[])
{
	int status;
	FILE *fileptr;
	
	if (argc != 2 ) 
	{
		fprintf(stderr, "This is how to properly run the program: %s filename\n", argv[0]);
		return 1;
	}
	status = compile(fileptr);
	fclose(fileptr);
	
	if (status == 0) 
	{
		status= execute();
	}
	
	if (status == 1) 
	{
		fprintf(stderr, "Error!\n");
	}
	
	return status;
}


