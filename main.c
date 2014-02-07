#include <stdio.h>
#include <stdlib.h>

//#define DEBUG

/* Binary Search Tree Data Structure */
typedef struct tree 
{
	int value;
	struct tree *parent;	/* pointer to parent */
	struct tree *left;	/* pointer to left child */
	struct tree *right;	/* pointer to right child */
} tree;



void insert_tree(int value, tree *node);
void delete_tree(int value, tree *node);
tree *search_tree(int value, tree *node);
tree *find_maximum(tree *node);
tree *find_minimum(tree *node);
void print_tree(tree *node);
int isBST(tree *node);
tree *find_successor(tree *node);
tree *find_predecessor(tree *node);
tree *find_kth_smallest(tree *node, int k);
tree *find_kth_largest(tree *node, int k);
tree *find_LCA(tree *node, int n1, int n2);


/*
 *	Insert a node to a BST
 */
void insert_tree(int value, tree *node)
{
	if (node == NULL)
		return;

	if (value < node->value) {
		if (node->left) {
			insert_tree(value, node->left);
		} else {
			node->left = calloc(1, sizeof(tree));
			(node->left)->value = value;
			(node->left)->left = NULL;
			(node->left)->right = NULL;
			(node->left)->parent = node;
		}

	} else {
		if (node->right) {
			insert_tree(value, node->right);
		} else {
			node->right = calloc(1,sizeof(tree));
			(node->right)->value = value;
			(node->right)->left = NULL;
			(node->right)->right = NULL;
			(node->right)->parent = node;	
		}
	}
}

/*
 *	Delete a node from a BST
 */
void delete_tree(int value, tree *node)
{
	tree *delete, *successor;

	delete = search_tree(value, node);
	
	/* no child */
	if (delete->left == NULL && delete->right == NULL) {
		if ((delete->parent)->left == delete) 
			(delete->parent)->left = NULL;
		else
			(delete->parent)->right = NULL;
		
		free(delete);
	} 
	/* only one child */
	else if (delete->left == NULL || delete->right == NULL) {
		if (delete->left) {
			(delete->parent)->left = delete->left;
		} else {
			(delete->parent)->right = delete->right;
		}
		free(delete);
	}
	/* two children: immediate successor is the smallest value in the right subtree */
	else if (delete->left && delete->right) {
		successor = find_minimum(delete->right);
		/* successor has no child */
		if (successor->left == NULL && successor->right == NULL) {
			delete->value = successor->value;
			if ((successor->parent)->left == successor) 
				(successor->parent)->left = NULL;
			else
				(successor->parent)->right = NULL;
			
			free(successor);
		}
		/* successor has a child */ 
		else {
			delete->value = successor->value;
			delete->right = successor->right;
			
			free(successor);
		}
	}
}

/*
 * Find a node that has a specific value in a BST
 */
tree *search_tree(int value, tree *node)
{
	if (node == NULL)
		return NULL;
	if (value == node->value)
		return node;
	if (value < node->value)
		return search_tree(value, node->left);
	else
		return search_tree(value, node->right);
}

/*
 * Find a node that has a maximum value in a BST
 */
tree *find_maximum(tree *node)
{
	tree *max;

	if (node == NULL)
		return NULL;

	max = node;
	while (max->right) {
		max = max->right;
	}
	return max;
}

/*
 * Find a node that has a minimum value in a BST
 */
tree *find_minimum(tree *node)
{
	tree *min;

	if (node == NULL)
		return NULL;

	min = node;
	while (min->left) {
		min = min->left;
	}
	return min;
}

/*
 * Print all values of nodes in a BST
 */
void print_tree(tree *node)
{
	if (node) {
		print_tree(node->left);
		printf(" %d ", node->value);
		print_tree(node->right);
	}
}

/*
 * Test whether a tree is BST or not
 */
int isBST(tree *node)
{
	if (node == NULL)
		return 1;
	if (node->left != NULL && find_maximum(node->left)->value > node->value)
		return 0;
	if (node->right != NULL && find_minimum(node->right)->value < node->value)
		return 0;
	if (!isBST(node->left) || !isBST(node->right))
		return 0;

	return 1;
}

/*
 * Find the successor element of a given node in a BST
 */
tree *find_successor(tree *node)
{
	tree *p;

	if (node->right)
		return find_minimum(node->right);

	p = node->parent;
	while((p != NULL) && (node == p->right)) {
		node = p;
		p = p->parent;
	}
	return p;
}

/*
 * Find the predecessor element of a given node in a BST
 */
tree *find_predecessor(tree *node)
{
	tree *p;

	if (node->left)
		return find_maximum(node->left);

	p = node->parent;
	while ((p != NULL) && (node == p->left)) {
		node = p;
		p = p->parent;
	}
	return p;
}

/*
 * Find the kth smallest element in a BST
 */
tree *find_kth_smallest(tree *node, int k)
{
	tree *item;

	item = find_minimum(node);
	while((item != NULL) && (k > 1)) {
#ifdef DEBUG
		printf(" %d ", item->value);
#endif
		--k;
		item = find_successor(item);
	}
	return item;
}

/*
 * Find the kth largest element in a BST
 */
tree *find_kth_largest(tree *node, int k)
{
	tree *item;

	item = find_maximum(node);
	while ((item != NULL) && (k > 1)) {
#ifdef DEBUG
		printf(" %d ", item->value);
#endif
		--k;
		item = find_predecessor(item);
	}
	return item;
}	


/*
 * Find a Lowest Common Ancestor in a BST
 */
tree *find_LCA(tree *node, int n1, int n2)
{
	if (node == NULL)
		return NULL;

	if (node->value > n1 && node->value > n2)
		return find_LCA(node->left, n1, n2);
	if (node->value < n1 && node->value < n2)
		return find_LCA(node->right, n1, n2);

	return node;	
}

/*
 * Operations using a BST
 */
int main()
{
	tree *root, *min;
	tree *lca, *kth;
	int k, n1, n2;

	root = (tree *)calloc(1, sizeof(tree));
	root->value = 5;
	root->left = root->right = root->parent = NULL;

	insert_tree(3, root);
	insert_tree(7, root);
	insert_tree(2, root);
	insert_tree(4, root);
	insert_tree(6, root);
	insert_tree(8, root);
	insert_tree(9, root);

	print_tree(root);
	printf("\n");

	if (isBST(root))
		printf("tree is a BST\n");
	else
		printf("tree is not a BST\n");

	k = 5;
	kth = find_kth_smallest(root, k);
	printf("%dth smallest value is %d\n", k, kth->value);

	k = 4;
	kth = find_kth_largest(root, k);
	printf("%dth largest value is %d\n", k, kth->value);

	n1 = 3;
	n2 = 7;
	lca = find_LCA(root, n1, n2);
	printf("Lowest Common Ancestor of %d and %d is %d\n", n1, n2, lca->value);

	n1 = 3;
	n2 = 8;
	lca = find_LCA(root, n1, n2);
	printf("Lowest Common Ancestor of %d and %d is %d\n", n1, n2, lca->value);

	delete_tree(7, root);
	print_tree(root);

	printf("\n");

	return 0;
}




