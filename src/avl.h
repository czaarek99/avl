#ifndef AVL_H
#define AVL_H

struct node {
    int key;
    unsigned int height;
    struct node* left;
    struct node* right;
};

struct node* make(int key, unsigned int height);
void destroy(struct node* node);
void add(struct node* node, int key);
void print_tree(struct node* node);

#endif
