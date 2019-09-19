#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

struct node* make(int key, unsigned int height) {
    struct node* n = calloc(1, sizeof(struct node));
    n->height = height;
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
            struct node* new_node = make(key, 0);
            node->left = new_node;
        } else {
            add(node->left, key);
        }
    } else {
        if(node->right == NULL) {
            struct node* new_node = make(key, 0);
            node->right = new_node;
        } else {
            add(node->right, key);
        }
    }

    node->height++;
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
