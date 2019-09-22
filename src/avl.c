#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

struct node* make(int key) {
	struct node* n = calloc(1, sizeof(struct node));
	n->count = 1;
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

int height(struct node* node) {
    if(node == NULL) {
        return -1;
    }

    return node->height;
}

struct node* rotate(struct node* node) {
	update_height(node);

	int leftHeight = height(node->left);
	int rightHeight = height(node->right);

	struct node* new_root = NULL;

	if(abs(leftHeight - rightHeight) > 1) {

	    if(node->right != NULL &&
            node->height - height(node->right) == 1 &&
            node->height - height(node->right->left) == 2) {

            right_rotate(node->right);
            new_root = left_rotate(node);
	    } else if(node->left != NULL &&
            node->height - height(node->left) == 1 &&
            node->height - height(node->left->right) == 2) {

            left_rotate(node->left);
            new_root = right_rotate(node);
	    } else if(node->left != NULL &&
            node->height - height(node->left) == 1 &&
            node->height - height(node->left->left) == 2) {

	    	new_root = right_rotate(node);
	    } else if(node->right != NULL &&
			node->height - height(node->right) == 1 &&
			node->height - height(node->right->right) == 2) {

	    	new_root = left_rotate(node);
	    }
	}

	if(new_root != NULL) {
		return new_root;
	}

	return node;
}

struct node* delete(struct node* node, int key) {

	if(key < node->key) {
		if(node->left == NULL) {
			return node;
		} else {
			delete(node->left, key);
		}
	} else if(key > node->key) {
		if(node->right == NULL) {
			return node;
		} else {
			delete(node->right, key);
		}
	} else {
		if(node->count > 1) {
			node->count--;
			return node;
		}

		//Leaf node
		if(node->right == NULL && node->left == NULL) {
			struct node* parent = node->parent;
			if(parent != NULL) {
                if(parent->left == node) {
                    parent->left = NULL;
                } else {
                    parent->right = NULL;
                }
			}
		} else if(node->right == NULL && node->left != NULL) {

			struct node* parent = node->parent;
			if(parent != NULL) {
				if(parent->left == node) {
					parent->left = node->left;
				} else {
					parent->right = node->left;
				}
			}

			node->left->parent = parent;
		} else if(node->right != NULL && node->left == NULL) {

			struct node* parent = node->parent;

			if(parent != NULL) {
				if(parent->left == node) {
					parent->left = node->right;
				} else {
					parent->right = node->right;
				}
			}

			node->right->parent = parent;
		} else {
			struct node* right_min = min_node(node->right);

			right_min->left = node->left;
			right_min->right = node->right;
			right_min->parent = node->parent;
		}

		free(node);
		return NULL;
	}

	return rotate(node);
}

struct node* add(struct node* node, int key) {
	if(node == NULL) {
		return make(key);
	}

	if(key < node->key) {
		if (node->left == NULL) {
			struct node* new_node = make(key);
			new_node->parent = node;

			node->left = new_node;
		} else {
			add(node->left, key);
		}
	} else if(key > node->key) {
		if(node->right == NULL) {
			struct node* new_node = make(key);
			new_node->parent = node;

			node->right = new_node;
		} else {
			add(node->right, key);
		}
	} else {
		node->count++;

		return node;
	}

	return rotate(node);
}

void print_tree(struct node* node) {

	if(node->left != NULL) {
		print_tree(node->left);
	}

	if(node->count > 1) {
		printf("%d(x%lu) ", node->key, node->count);
	} else {
		printf("%d ", node->key);
	}

	if(node->right != NULL) {
		print_tree(node->right);
	}
}

struct node* min_node(struct node* node) {

	if(node->left == NULL) {
		return node;
	} else {
		return min_node(node->left);
	}

}

struct node* max_node(struct node* node) {

	if(node->right == NULL) {
		return node;
	} else {
		return max_node(node->right);
	}

}

struct node* node_successor(struct node* node) {

	if(node->right != NULL) {
		return min_node(node->right);
	}

	struct node* parent = node->parent;

	while(parent != NULL && node == parent->right) {
		node = parent;
		parent = parent->parent;
	}

	return parent;
}

//TODO: Implement
struct node* node_predecessor(struct node* node) {
    return NULL;
}
