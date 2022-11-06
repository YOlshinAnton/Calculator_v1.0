#include <stdlib.h>
#include <stdio.h>

#include "list.h"

struct node* init_list(void * item) {
    struct node* root = NULL;
    root = malloc(sizeof(struct node));
    root -> next = NULL;
    root -> item = item;
    return root;
}

struct node* add_item(void * item, struct node* node) {
    struct node* new_node = NULL;
    if (node) {
        new_node = malloc(sizeof(struct node));
        new_node -> item = item;
        new_node -> next = node -> next;
        node -> next = new_node;
    }
    return new_node;
}

struct node* find_item(void * item, struct node* root) {
    while (root != NULL) {
        if (root -> item == item) {
            break;
        }
        root = root -> next;
    }
    return root;
}

struct node* remove_item(struct node* node, struct node* root) {
    struct node* desired_node = NULL;
    while (root) {
        if (root -> next == node) {
            desired_node = root -> next;
            root -> next = desired_node -> next;
            desired_node -> next = NULL;
        }
        root = root -> next;
    }
    return desired_node;
}

void destroy_list(struct node* root, void (*free_item)(void* item)) {
    while (root && root -> next) {
        struct node* prev = root -> next; root -> next = prev -> next;
        void* item = extract_item(prev);
        if (free_item) {
            free_item(item);
        }
        free(prev);
    }
    if (root) {
        void * item = extract_item(root);
        if (free_item) {
            free_item(item);
        }
        free(root);
    }
}

struct node* next_node(struct node* node) {
    if (node) {
        return node -> next;
    }
    return NULL;
}

size_t count_nodes(struct node* root) {
    int count = 0;
    while (root != NULL) {
        ++count;
        root = root->next;
    }
    return count;
}

void* extract_item(struct node* node) {
    return node -> item;
}
