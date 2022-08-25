#include "bintree.h"

// Preorder P L R
void	preorder(bintree_node *tree_node)
{
	if (!tree_node)
		return ;
	printf("%d ", tree_node->data);
	tree_node->visited = 1;
	preorder(tree_node->left_child);
	preorder(tree_node->right_child);
}

// Inorder L P R
void	inorder(bintree_node *tree_node)
{
	if (!tree_node)
		return ;
	tree_node->visited = 1;
	inorder(tree_node->left_child);
	printf("%d ", tree_node->data);
	inorder(tree_node);
	inorder(tree_node->right_child);
}

// Postorder L R P
void	postorder(bintree_node *tree_node)
{
	if (!tree_node)
		return ;
	tree_node->visited = 1;
	postorder(tree_node->left_child);
	postorder(tree_node->right_child);
	postorder(tree_node);
	printf("%d ", tree_node->data);
}
