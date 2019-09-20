#include <stdio.h>
#include "avl.h"

int main() {
    struct node* root = make(41);

    add(root, 20);
    add(root, 29);
    add(root, 26);
    add(root, 11);
    add(root, 65);
    add(root, 50);

    print_tree(root);

    return 0;
}