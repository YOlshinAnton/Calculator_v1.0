#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include "list.h"

typedef struct stack {
    struct node* list_root;
    int count;
} t_stack;

t_stack * init_stack();
void push(t_stack* stack, void* item);
void* pop(t_stack* stack);
void* peek(t_stack* stack);
void destroy_stack(t_stack* stack, void (*free_item)(void* item));

#endif  // SRC_STACK_H_
