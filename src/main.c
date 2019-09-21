#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"

int random(int min, int max){
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int main() {
    struct node* root = make(41);

    srand(time(NULL));

    for(int i = 0; i < 20; i++) {
        root = add(root, random(-50, 200));
    }

    print_tree(root);

    return 0;
}