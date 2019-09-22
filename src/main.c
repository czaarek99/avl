#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"

int random(int min, int max){
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int main() {

	/*srand(time(NULL));

	for(int i = 0; i < 20; i++) {
		root = add(root, random(-50, 200));
	}*/

    struct node* root = add(NULL, 60);
	root = add(root, 30);
    root = add(root, 30);
	root = add(root, 70);
	root = add(root, 29);
	root = add(root, 32);
	root = add(root, 71);
	root = add(root, 69);

	print_tree(root);

	/*root = delete(root, 29);
    root = delete(root, 30);
    root = delete(root, 30);
    root = delete(root, 32);

	printf("\n");*/

    print_tree(root);

	return 0;
}