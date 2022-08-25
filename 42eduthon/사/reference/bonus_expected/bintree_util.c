#include "bintree.h"

bintree_node	*get_left_child_node_bt(bintree_node *node)
{
	if (node == NULL)
		return (NULL);
	return (node->left_child);
}

bintree_node	*get_right_child_node_bt(bintree_node *node)
{
	if (node == NULL)
		return (NULL);
	return (node->right_child);
}

void	delete_bintree(bintree *bt)
{
	if (bt)
	{
		delete_bintree_node(&bt->root_node);
		free(bt);
	}
}

void	delete_bintree_node(bintree_node **node)
{
	if (*node)
	{
		delete_bintree_node(&(*node)->left_child);
		delete_bintree_node(&(*node)->right_child);
		free(*node);
		*node = NULL;
	}
}
