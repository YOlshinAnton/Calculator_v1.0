#include "stack.h"
#include <stdio.h>

t_stack* init_stack() {
    t_stack* stack = malloc(sizeof(t_stack));
    stack -> list_root = init_list(0);
    stack -> count = 0;
    return stack;
}

void push(t_stack* stack, void* item) {
    add_item(item, stack -> list_root);
    stack -> count++;
}

void* pop(t_stack* stack) {
    struct node* node = NULL;
    void* item = NULL;
    if (stack->count > 0) {
        node = remove_item(stack -> list_root -> next, stack -> list_root);
        item = node -> item; free(node);
        stack -> count--;
    }
    return item;
}

void destroy_stack(t_stack* stack, void (*free_item)(void* item)) {
    destroy_list(stack -> list_root, free_item);
    free(stack);
}
