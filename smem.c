// smem.c
// Ben Crabtree, 2021

// A stack machine emulator
// Reads instructions from a text file, maintains an indexable instruction array and instruction pointer and uses these to manipulate a virtual memory stack which stores integers.

// Command line arguments:
// - File name of text file storing stack machine program
// - Number of instructions in stack machine program

// Instructions:
// - <integer>: A positive integer from 0 to INT_MAX (+2,147,483,647). Pushes <integer> onto the stack
// (REMOVE?) - POP: Pops top element off stack
// - DUP: Pushes another copy of the top element onto the stack
// - ADD: Pops top two elements off stack, adds them together and pushes the result onto the stack
// - SUB: Pops top two elements off stack, subtracts the first (top) from the second and pushes the result onto the stack
// - SIZ: Push current stack size onto stack (eg If stack has four elements, will push 4 onto stack, and new stack size will be five elements)
// (REMOVE?) - JMP: Pops top element <i> off the stack and jumps to instruction in index <i> of instruction array
// - JNE: Pops top element <i> (jump index), second top element <j> (comparison value) and third top element <k> (counter) of the stack. If <k> is not equal to <j>, jump to instruction in index <i> of the instruction array.
// - RET: Returns top element of stack and terminates stack machine program.
// - <comment>: Any line beginning with a ';' is treated as a comment and ignored (not added to instruction array or evaluated)
// Any blank line in the text file will also not be added to instruction array or evaluated

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// Do I need to include smem_stack.h here if including in smem_instructions?
//# include "smem_stack.h"

# include "smem_instructions.h"

char** init_instruction_array(FILE* fp, int n)
{
	char** instruction_array = malloc( n * sizeof(char*) );
	char line[256];
	int i = 0;
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		//printf("line[0]: %d\n", (int)line[0]);
		// Check first character of line is not ';' (ascii 59), newline (10) or carriage return (13)
		if ((int)line[0] != 59 && (int)line[0] != 10 && (int)line[0] != 13)
		{
			// Each line has a '\n' at the end - remove it
			line[strlen(line) - 1] = '\0';
			char* op = malloc( strlen(line) * sizeof(char) );
			//printf("line[0]: %d\n", (int)line[0]);
			//printf("strlen line: %ld\n", strlen(line));
			strcpy(op, line);
			//op = line;
			//printf("op: %s\n", op);
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
	print_instruction_array(instruction_array, num_instructions);
	
	// Parse and execute instructions:
	
	// Initialise instruction pointer
	int ip = 0;	
	// Initialise empty stack (value of node set to -1)
	SNode* head = snode_init(-1, ip);
	//head->is_head = true;
	// Get first instruction
	char* op = instruction_array[ip];
	// If RET is first instruction, return -1
	//if (strcmp(op, "RET") == 0)
	//	printf("Return value: %d\n", head->value);
	//	return 0;
	// Loop over instruction_array using instruction pointer
	//printf("op: %s\n", op);
	//printf("num_instructions - 1: %d\n", num_instructions - 1);
	while (ip > -1 && ip < num_instructions)
	{
		printf("Inside main while loop,\n");
		printf("ip: %d\n", ip);
		printf("op: %s\n", op);
		printf("head value: %d\n", head->value);
		// parse_instruction takes an op & the stack, executes the operation and returns a new instruction pointer value
		// The RET op sets the instruction pointer to -1, terminating the while loop
		head = parse_instruction(op, head, ip);
		ip = head->ip;
		//printf("ip: %d\n", ip);
		if (ip < 0 || ip >= num_instructions)
		{
			printf("Break\n");
			break;
		}
		//printf("Getting new instruction.\n");
		op = instruction_array[ip];
		printf("\n");
		printf("Stack: ");
		stack_print(head);
	}
	//return head->value; // Once done executing instructions, return the value of the head of the list
	printf("Final stack: \n");
	stack_print(head);
	printf("Return value: %d\n", head->value);
	return 0;
}
