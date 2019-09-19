#include <stdio.h>
#include "avl.h"

int main() {
    struct node* root = make(10, 0);

    add(root, 2);
    add(root, 6);
    add(root, 25);
    add(root, 100);
    add(root, 1);
    add(root, 35);
    add(root, 35);
    add(root, 35);
    add(root, 35);
    add(root, 1000);
    add(root, -5);
    add(root, 500);

    print_tree(root);

    return 0;
}