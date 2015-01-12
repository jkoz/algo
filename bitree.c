#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bitree.h"

void bitree_init(BiTree *tree, void (*destroy)(void *data)) {
	tree->size = 0;
	tree->destroy = destroy;
	tree->root = NULL;
}

void bitree_destroy(BiTree *tree) {
	/** TODO: check here  Remove all the nodes from the tree.*/
	bitree_rem_left(tree, NULL);

	memset(tree, 0, sizeof(BiTree));
	return;
}

int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data) {
	BiTreeNode *new_node, **position;

	if (node == NULL) {
		/*Allow insertion at the root only in an empty tree.*/
		if (bitree_size(tree) > 0)
			return -1;
		position = &tree->root;
	} else {
		/*Normally allow insertion only at the end of a branch.*/
	   if (bitree_left(node) != NULL)
			return -1;
		position = &node->left;
	}

	if ((new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL)
		return -1;

	/* Insert the node into the tree. */
	new_node->data = (void *)data;
	new_node->left = NULL;
	new_node->right = NULL;
	*position = new_node;

	tree->size++;

	return 0;
}

int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data) {
	BiTreeNode *new_node, **position;

	if (node == NULL) {
		/*Allow insertion at the root only in an empty tree.*/
		if (bitree_size(tree) > 0)
			return -1;
		position = &tree->root;
	} else {
		/*Normally allow insertion only at the end of a branch.*/
	   if (bitree_right(node) != NULL)
			return -1;
		position = &node->right;
	}

	if ((new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL)
		return -1;

	/* Insert the node into the tree. */
	new_node->data = (void *)data;
	new_node->left = NULL;
	new_node->right = NULL;
	*position = new_node;

	tree->size++;
	return 0;
}

void bitree_rem_left(BiTree *tree, BiTreeNode *node) {
	BiTreeNode **position;

	/*Do not allow remove from empty tree*/
	if (bitree_size(tree) == 0)
		return;

	/*Determine where to remove*/
	if (node == NULL)
		position = &tree->root;
	else
		position = &node->left;

	/*Remove the node*/
	if (*position != NULL) {
		bitree_rem_left(tree, *position);
		bitree_rem_right(tree, *position);

		if (tree->destroy != NULL) {
			tree->destroy((*position)->data);
		}

		/* free the position */
		free(*position);
		*position = NULL;

		/*Adjust the size of the tree to account for the removed node.*/
		tree->size--;
	}
}
void bitree_rem_right(BiTree *tree, BiTreeNode *node) {
	BiTreeNode **position;

	/**  Do not allow removal from an empty tree.      */
	if (bitree_size(tree) == 0)
		return;

	 /*Determine where to remove nodes.*/
	if (node == NULL)
		position = &tree->root;
	else
		position = &node->right;

	/*Remove the node*/
	if (*position != NULL) {
		bitree_rem_left(tree, *position);
		bitree_rem_right(tree, *position);

		if (tree->destroy != NULL) {
			tree->destroy((*position)->data);
		}

		/* free the position */
		free(*position);
		*position = NULL;

		/*Adjust the size of the tree to account for the removed node.*/
		tree->size--;
	}
}

int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data) {
	bitree_init(merge, left->destroy);

	/*Insert the data for the root node of the merged tree.*/
	if (bitree_ins_left(merge, NULL, data) != 0) {
		bitree_destroy(merge);
		return -1;
	}

	/*Merge the two binary trees into a single binary tree. (shallow)*/
	bitree_root(merge)->left = bitree_root(left);
	bitree_root(merge)->right = bitree_root(right);


    /*Adjust the size of the new binary tree.*/
	merge->size = merge->size + bitree_size(left) + bitree_size(right);

    /*Do not let the original trees access the merged nodes.*/
	left->root = NULL;
	left->size = 0;
	right->root = NULL;
	right->size = 0;
	return 0;
}


int bitree_preorder_traverse(const BiTreeNode *node, int (*handler)(void *)) {
	if (!bitree_is_eob(node)) {

		/*data*/
		if (handler(node->data) != 0) return -1;

		/*left*/
		if (!bitree_is_eob(bitree_left(node)))
			if (bitree_preorder_traverse(bitree_left(node), handler) != 0)
				return -1;

		/*right*/
		if (!bitree_is_eob(bitree_right(node)))
			if (bitree_preorder_traverse(bitree_right(node), handler) != 0)
				return -1;
	}
	return 0;
}

int bitree_inorder_traverse(const BiTreeNode *node, int (*handler)(void *)) {
	if (!bitree_is_eob(node)) {
		/*left*/
		if (!bitree_is_eob(bitree_left(node)))
			if (bitree_inorder_traverse(bitree_left(node), handler) != 0)
				return -1;

		/*data*/
		if (handler(node->data) != 0) return -1;

		/*right*/
		if (!bitree_is_eob(bitree_right(node)))
			if (bitree_inorder_traverse(bitree_right(node), handler) != 0)
				return -1;
	}
	return 0;
}

int bitree_postorder_traverse(const BiTreeNode *node, int (*handler)(void *)) {
	if (!bitree_is_eob(node)) {
		/*left*/
		if (!bitree_is_eob(bitree_left(node)))
			if (bitree_postorder_traverse(bitree_left(node), handler) != 0)
				return -1;

		/*right*/
		if (!bitree_is_eob(bitree_right(node)))
			if (bitree_postorder_traverse(bitree_right(node), handler) != 0)
				return -1;

		/*data*/
		if (handler(node->data) != 0) return -1;
	}
	return 0;
}

void bitree_print(const BiTree *tree) {

}
