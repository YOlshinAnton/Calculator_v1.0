#ifndef SRC_LIST_H_
#define SRC_LIST_H_

#include <stdlib.h>

struct node {
    struct node* next;
    void * item;
};
typedef struct node* list_t;

struct node* copy_list();
struct node* init_list(void * item);
void destroy_list(struct node* root, void (*free_item)(void* item));

struct node* add_item(void * item, struct node* root);
struct node* find_item(void * item, struct node* root);
struct node* remove_item(struct node* node, struct node* root);
struct node* next_node(struct node* node);

void* extract_item(struct node* node);
size_t count_nodes(struct node* root);

#endif  // SRC_LIST_H_
