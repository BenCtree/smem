// smem_instructions.h
// Ben Crabtree, 2021

# ifndef SMEM_INSTRUCTIONS_H
# define SMEM_INSTRUCTIONS_H

# include "smem_stack.h"

//SNode* push_int()

SNode* int_check(char* op, SNode* head, int ip);
SNode* dup_check(char* op, SNode* head, int ip);
SNode* add_check(char* op, SNode* head, int ip);
SNode* sub_check(char* op, SNode* head, int ip);
SNode* siz_check(char* op, SNode* head, int ip);
SNode* jne_check(char* op, SNode* head, int ip);
SNode* ret_check(char* op, SNode* head, int ip);
SNode* parse_instruction(char* op, SNode* head, int ip);

# endif
