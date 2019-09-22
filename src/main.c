#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"

int random(int min, int max){
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int main() {
	struct node* root = make(41);

	/*srand(time(NULL));

	for(int i = 0; i < 20; i++) {
		root = add(root, random(-50, 200));
	}*/

	root = add(root, 50);
	root = add(root, 50);
	root = add(root, 50);
	root = add(root, 50);
	root = add(root, 50);
	root = add(root, 50);
	root = add(root, 60);
	root = add(root, -5);
	root = add(root, 70);

	print_tree(root);

	struct node* s = successor(root, 30);

	if(s != NULL) {
		printf("\n successor: %d\n", s->key);
	} else {
		printf("\n no successor");
	}


	return 0;
}