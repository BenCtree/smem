// smem.c
// Ben Crabtree, 2021

// A stack machine emulator
// Reads instructions from a text file, maintains an indexable instruction array and instruction pointer and uses these to manipulate a virtual memory stack which stores integers.

// Command line arguments:
// - File name of text file storing stack machine program
// - Number of instructions in stack machine program

# include "smem_instructions.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

char** init_instruction_array(FILE* fp, int n)
{
	char** instruction_array = malloc( n * sizeof(char*) );
	char line[256];
	int i = 0;
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		// Check first character of line is not ';' (ascii 59), newline (10) or carriage return (13)
		if ((int)line[0] != 59 && (int)line[0] != 10 && (int)line[0] != 13)
		{
			// Each line has a '\n' at the end - remove it
			line[strlen(line) - 1] = '\0';
			char* op = malloc( strlen(line) * sizeof(char) );
			strcpy(op, line);
			instruction_array[i] = op;
			i++;
		}
	}
	return instruction_array;
}

void print_instruction_array(char** instruction_array, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("Instruction %d:\t%s\n", i, instruction_array[i]);
	}
}

int main(int argc, char* argv[])
{
	// Check if text file name provided
	if (argc < 3)
	{
		printf("Please enter a stack program text file name and a number of instructions.\n");
		return 1;
	}

	// Check if too many arguments provided
	if (argc > 3)
	{
		printf("Too many arguments.\n");
		return 1;
	}

	// Get file name and open file
	char* filename = argv[1];
	int num_instructions = atoi(argv[2]);
	FILE* fp = fopen(filename, "r");

	// Check if file exists
	if (fp == NULL)
	{
		printf("Could not open file.\n");
		return 1;
	}

	// Check if file is empty
	if (fp == NULL)
	{
		fseek(fp, 0, SEEK_END);
		if (ftell(fp) == 0)
		{
			printf("File is empty.\n");
			return 1;
		}
	}
	
	// Read instructions from file into instruction array	
	char** instruction_array = init_instruction_array(fp, num_instructions);
	//print_instruction_array(instruction_array, num_instructions);
	
	// Parse and execute instructions:
	
	// Initialise instruction pointer
	int ip = 0;	
	// Initialise empty stack (value of node set to -1)
	SNode* head = snode_init(-1, ip);
	// Get first instruction
	char* op = instruction_array[ip];
	while (ip > -1 && ip < num_instructions)
	{
		// parse_instruction takes an op & the stack, executes the operation and returns a new instruction pointer value
		// The RET op sets the instruction pointer to -1, terminating the while loop
		head = parse_instruction(op, head, ip);
		ip = head->ip;
		if (ip < 0 || ip >= num_instructions)
		{
			printf("Break\n");
			break;
		}
		op = instruction_array[ip];
		printf("Stack: ");
		stack_print(head);
		printf("\n");
	}
	printf("Final stack: \n");
	stack_print(head);
	printf("Return value: %d\n", head->value);
	return 0;
}

