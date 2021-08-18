// smem_stack.h
// Ben Crabtree, 2021

# ifndef SMEM_STACK_H
# define SMEM_STACK_H

# include <stdbool.h>

struct stack_node
{
	int value;
	int ip;
	struct stack_node* next;
	bool is_head;
};

typedef struct stack_node SNode;

SNode* snode_init(int value, int ip);

SNode* stack_push(SNode* head, SNode* node);

SNode* stack_pop(SNode* head);

int stack_size(SNode* head);

void stack_print(SNode* head);

# endif
