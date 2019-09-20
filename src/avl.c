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

//https://www.tutorialspoint.com/data_structures_algorithms/avl_tree_algorithm.htm
struct node* left_rotate(struct node* node) {
    struct node* top_node = node->right;
    struct node* left_node = node;

    top_node->parent = left_node->parent;
    top_node->left = left_node;

    left_node->parent = top_node;
    left_node->right = NULL;
    
    return top_node;
}

//https://www.tutorialspoint.com/data_structures_algorithms/avl_tree_algorithm.htm
struct node* right_rotate(struct node* node) {
    struct node* top_node = node->left;
    struct node* right_node = node;

    top_node->parent = right_node->parent;
    top_node->right = right_node;

    right_node->parent = top_node;
    right_node->left = NULL;

    return top_node;
}

void update_height(struct node* node) {
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

void add(struct node* node, int key) {
    if(key <= node->key) {
        if (node->left == NULL) {
            struct node* new_node = make(key);
            new_node->parent = node;

            node->left = new_node;
        } else {
            add(node->left, key);
        }
    } else {
        if(node->right == NULL) {
            struct node* new_node = make(key);
            new_node->parent = node;

            node->right = new_node;
        } else {
            add(node->right, key);
        }
    }

    update_height(node);

    int leftHeight = -1;
    int rightHeight = -1;

    if(node->left != NULL) {
        leftHeight = node->left->height;
    }

    if(node->right != NULL) {
        rightHeight = node->right->height;
    }

    if(abs(leftHeight - rightHeight) > 1) {

        if(node->left == NULL &&
            node->right != NULL &&
            node->right->left == NULL &&
            node->right->right != NULL) {

            left_rotate(node);
        } else if(node->right == NULL &&
            node->left != NULL &&
            node->left->right == NULL &&
            node->left->left != NULL) {

            right_rotate(node);
        } else if(node->right == NULL &&
            node->left != NULL &&
            node->left->left == NULL &&
            node->left->right != NULL) {

            left_rotate(node->left);
            right_rotate(node);
        } else if(node->left == NULL &&
            node->right != NULL &&
            node->right->right == NULL &&
            node->right->left != NULL) {

            right_rotate(node->right);
            left_rotate(node);
        }
    }

    printf("");
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
