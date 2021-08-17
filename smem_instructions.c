// smem_instructions.c
// Ben Crabtree, 2021

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "smem_instructions.h"

SNode* int_check(char* op, SNode* head, int ip)
{
	//printf("atoi(op): %d\n", atoi(op));
	int num = atoi(op);
	if (num < 0)
	{
		printf("ERROR: Integer to push on stack must be positive.\n");
		head->ip = -1;
		return head;
		//SNode* error_node = snode_init(-1, -1);
		//return error_node;
	}
	//ip++;
	SNode* node = snode_init(num, ip + 1);
	head = stack_push(head, node);
   	printf("Pushed %d onto stack\n", num);
	return head;
}

SNode* dup_check(char* op, SNode* head, int ip)
{
	if (head->value == -1)
	{
		printf("ERROR: Stack empty.\n");
		head->ip = -1;
		return head;
		//SNode* error_node = snode_init(-1, -1);
		//return error_node;
	}
	SNode* node = snode_init(head->value, ip + 1);
	head = stack_push(head, node);
	printf("Executed DUP.\n");
	return head;
}

SNode* add_check(char* op, SNode* head, int ip)
{
	if (head->value == -1 || head->next == NULL)
	{
		printf("ERROR: Stack must contain at least two elements.\n");
		head->ip = -1;
        return head;
	}
	int top_val = head->value;
	SNode* top_node = head;
	head = stack_pop(head);
	free(top_node);
	//int second = head->value;
	//SNode* second_node = head;
	//head = stack_pop(head);
	//free(second_node);
	head->value += top_val;
	head->ip = ip + 1;
	//int result = top + second;
	//SNode* node = snode_init(result, ip + 1);
	//head = stack_push(head, node);
	printf("Executed ADD.\n");
	return head;
}

SNode* sub_check(char* op, SNode* head, int ip)
{
	if (head->value == -1 || head->next == NULL)
	{
		printf("ERROR: Stack must contain at least two elements.\n");
		head->ip = -1;
        return head;
	}
	int top_value = head->value;
	SNode* top_node = head;
	head = stack_pop(head);
	free(top_node);
	int second_value = head->value;
	//SNode* second_node = head;
	//head = stack_pop(head);
	//free(second_node);
	//head->value -= top_value
	int result = top_value - second_value;
	if (result < 0)
	{
		printf("ERROR: Negative subtraction result.\n");
		head->ip = -1;
        return head;
	}
	head->value = result;
	head->ip = ip + 1;
	//SNode* node = snode_init(result, ip + 1);
	//head = stack_push(head, node);
	printf("Executed SUB.\n");
	return head;
}

SNode* siz_check(char* op, SNode* head, int ip)
{
	if (head->value == -1)
	{
		head->value = 0;
		head->ip = ip + 1;
		printf("Executed SIZ.\n");
		return head;
	}
	int size = stack_size(head);
	/*
	int counter = 0;
	SNode* curr = head;
	while (curr != NULL)
	{
		counter++;
		curr = curr->next;
	}
	*/
	SNode* node = snode_init(size, ip + 1);
	head = stack_push(head, node);
	printf("Executed SIZ: %d\n", size);
	return head;
}

SNode* jne_check(char* op, SNode* head, int ip)
{
	if (head->value == -1 || head->next == NULL || head->next->next == NULL)
	{
		printf("ERROR: Stack must contain at least three elements.\n");
		head->ip = -1;
        return head;
	}
	int jump_index = head->value;
	SNode* top = head;
	head = stack_pop(head);
	free(top);
	int comparison_val = head->value;
	SNode* second = head;
	head = stack_pop(head);
	free(second);
	int counter = head->value;
	SNode* third = head;
	head = stack_pop(head);
	free(third);
	if (counter != comparison_val)
	{
		printf("Executed jump.\n");
		head->ip = jump_index;
		return head;
	}
	printf("No jump.\n");
	head->ip = ip + 1;
	printf("ip: %d\n", head->ip);
	return head;
}

/*
SNode* ret_check(char* op, SNode* head, int ip)
{
	head->ip = -1;
	return head;
}
*/

SNode* parse_instruction(char* op, SNode* head, int ip)
{
	int res;
	// Check if op is a positive integer
	if (atoi(op) != 0)
	{
		SNode* node = int_check(op, head, ip);
		return node;
	}
	// Check conditions for DUP instruction are met
	if (strcmp(op, "DUP") == 0)
	{
		SNode* node = dup_check(op, head, ip);
		return node;
	}
	if (strcmp(op, "ADD") == 0)
	{
		SNode* node = add_check(op, head, ip);
		return node;
	}
	if (strcmp(op, "SUB") == 0)
   	{
   		SNode* node = sub_check(op, head, ip);
   		return node;
   	}
	if (strcmp(op, "SIZ") == 0)
   	{
   		SNode* node = siz_check(op, head, ip);
   		return node;
   	}
	if (strcmp(op, "JNE") == 0)
   	{
   		SNode* node = jne_check(op, head, ip);
   		return node;
   	}
	/*
	if (strcmp(op, "RET") == 0)
   	{
   		SNode* node = ret_check(op, head, ip);
   		return node;
   	}
	*/
	// If op is not recognised as a valid instruction
	printf("ERROR: %s not a valid instruction.\n", op);
	SNode* error_node = snode_init(-1, -1);
	return error_node;
}
