#include "list.h"

#include <stdio.h>

int main(void) {

    list_t integers = init_list(0);
    
    list_t tail = integers;
    for (long i = 1; i < 10; ++i)
    {
        tail = add_item((void*)i, tail);
    }

    list_t head = integers;
    list_t next;
    while (head -> next) {
        next = next_node(head);
        
    }
    

    destroy_list(integers, NULL);
    return 0; 
}
