// smem_stack.c
// Ben Crabtree, 2021

# include <stdio.h>
# include <stdlib.h>
# include "smem_stack.h"

SNode* snode_init(int value, int ip)
{
	SNode* snode = malloc(sizeof(SNode));
	snode->value = value;
	snode->ip = ip;
	snode->next = NULL;
	snode->is_head = true;
	return snode;
}

// Instert node before head and make node new head
SNode* stack_push(SNode* head, SNode* node)
{
	if (head->value == -1)
	{
		head->value = node->value;
		head->ip = node->ip;
		return head;
	}
	node->next = head;
	head->is_head = false;
	//node->is_head = true; //Already set to true in snode_init
	return node;
}

// Pop head and make next node new head
// Return list minus first node
SNode* stack_pop(SNode* head)
{
	if (head->next == NULL)
	{
		head->value = -1;
		//head->ip
		return head;
	}
	SNode* node = head;
	node->is_head = false;
	head = head->next;
	node->next = NULL;
	head->is_head = true;
	return head;
}

int stack_size(SNode* head)
{
	int size = 0;
	SNode* curr = head;
	while (curr != NULL)
	{
		size++;
		curr = curr->next;
	}
	return size;
}

void stack_print(SNode* head)
{
	int size = stack_size(head);
	printf("Inside stack_print, stack size: %d\n", size);
	SNode* curr = head;
	for (int i = 0; i < size; i++)
	{
		printf("{%d}", curr->value);
		if (curr->next != NULL)
			printf(" -> ");
		curr = curr->next;
	}
	/*
	SNode* curr = head;
	if (curr->next = NULL)
	{
		printf("{%d}\n", curr->value);
		return;
	}
	while (curr != NULL)
	{
		printf("{%d}", curr->value);
		if (curr->next != NULL)
			printf(" -> ");
		curr = curr->next;
	}
	*/
	printf("\n");
}

/*
int main()
{
	SNode* head = snode_init(0);
	for (int i = 1; i < 10; i++)
	{
		SNode* node = snode_init(i);
		head = stack_push(head, node);
	}

	int size = stack_size(head);
	printf("Size: %d\n", size);

	stack_print(head);

	SNode* node = head;
	head = stack_pop(head);
	printf("Size: %d\n", stack_size(head));
	//printf("node: \n");
	stack_print(node);
	//printf("head: \n");
	stack_print(head);

	SNode* node2 = head;
	head = stack_pop(head);
	printf("Size: %d\n", stack_size(head));
	stack_print(node2);
	stack_print(head);
}
*/
