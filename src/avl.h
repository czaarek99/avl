#ifndef AVL_H
#define AVL_H

struct node {
    int key;
    int height;
    unsigned long count;
    struct node* parent;
    struct node* left;
    struct node* right;
};


struct node* make(int key);
void destroy(struct node* node);
struct node* min_node(struct node* node);
struct node* max_node(struct node* node);
struct node* add(struct node* node, int key);
struct node* delete(struct node* node, int key);
//struct node* successor(struct node* node, int key);
//struct node* predecessor(struct node* node, int key);
void print_tree(struct node* node);

#endif
