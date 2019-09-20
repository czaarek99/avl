#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

struct node* make(int key) {
    struct node* n = calloc(1, sizeof(struct node));
    n->height = 0;
    n->key = key;
    return n;
}

void destroy(struct node* node) {

    if(node->left != NULL) {
        destroy(node->left);
        free(node->left);
    }

    if(node->right != NULL) {
        destroy(node->right);
        free(node->right);
    }

    free(node);
}

void add(struct node* node, int key) {
    if(key <= node->key) {
        if (node->left == NULL) {
            struct node* new_node = make(key);
            node->left = new_node;
        } else {
            add(node->left, key);
        }
    } else {
        if(node->right == NULL) {
            struct node* new_node = make(key);
            node->right = new_node;
        } else {
            add(node->right, key);
        }
    }

    int leftHeight = -1;
    int rightHeight = -1;

    if(node->left != NULL) {
        leftHeight = node->left->height;
    }

    if(node->right != NULL) {
        rightHeight = node->right->height;
    }

    if(leftHeight >= rightHeight) {
        node->height = leftHeight + 1;
    } else {
        node->height = rightHeight + 1;
    }
}


void print_tree(struct node* node) {

    if(node->left != NULL) {
        print_tree(node->left);
    }

    printf("%d ", node->key);

    if(node->right != NULL) {
        print_tree(node->right);
    }
}
