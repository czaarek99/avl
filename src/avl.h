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
struct node* add(struct node* node, int key);
void print_tree(struct node* node);

#endif
