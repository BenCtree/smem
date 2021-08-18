// smem_stack.c
// Ben Crabtree, 2021

# include "smem_stack.h"

# include <stdio.h>
# include <stdlib.h>

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
	return node;
}

// Pop head and make next node new head
// Return list minus first node
SNode* stack_pop(SNode* head)
{
	if (head->next == NULL)
	{
		head->value = -1;
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
	SNode* curr = head;
	for (int i = 0; i < size; i++)
	{
		printf("{%d}", curr->value);
		if (curr->next != NULL)
			printf(" -> ");
		curr = curr->next;
	}
	printf("\n");
}

