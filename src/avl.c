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

//https://www.tutorialspoint.com/data_structures_algorithms/avl_tree_algorithm.htm
struct node* left_rotate(struct node* node) {
    struct node* top_node = node->right;
    struct node* left_node = node;
    struct node* right_node = node->right->right;

    top_node->parent = left_node->parent;
    top_node->left = left_node;

    if(left_node->parent != NULL) {
        if(left_node->parent->right == left_node) {
            left_node->parent->right = top_node;
        } else {
            left_node->parent->left = top_node;
        }
    }

    left_node->parent = top_node;
    left_node->right = NULL;

    update_height(left_node);

    if(right_node != NULL) {
        update_height(right_node);
    }

    update_height(top_node);

    return top_node;
}

//https://www.tutorialspoint.com/data_structures_algorithms/avl_tree_algorithm.htm
struct node* right_rotate(struct node* node) {
    struct node* top_node = node->left;
    struct node* right_node = node;
    struct node* left_node = node->left->left;

    top_node->parent = right_node->parent;
    top_node->right = right_node;

    if(right_node->parent != NULL) {
        if(right_node->parent->left == right_node) {
            right_node->parent->left = top_node;
        } else {
            right_node->parent->right = top_node;
        }
    }

    right_node->parent = top_node;
    right_node->left = NULL;

    update_height(right_node);

    if(left_node != NULL) {
        update_height(left_node);
    }

    update_height(top_node);

    return top_node;
}

struct node* add(struct node* node, int key) {
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

    struct node* new_root = NULL;

    if(abs(leftHeight - rightHeight) > 1) {

        if(node->left == NULL &&
            node->right != NULL &&
            node->right->left == NULL &&
            node->right->right != NULL) {

            new_root = left_rotate(node);
        } else if(node->right == NULL &&
            node->left != NULL &&
            node->left->right == NULL &&
            node->left->left != NULL) {

            new_root = right_rotate(node);
        } else if(node->right == NULL &&
            node->left != NULL &&
            node->left->left == NULL &&
            node->left->right != NULL) {

            left_rotate(node->left);
            new_root = right_rotate(node);
        } else if(node->left == NULL &&
            node->right != NULL &&
            node->right->right == NULL &&
            node->right->left != NULL) {

            right_rotate(node->right);
            new_root = left_rotate(node);
        }
    }

    if(new_root != NULL && new_root->parent == NULL) {
        return new_root;
    }

    return node;
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
