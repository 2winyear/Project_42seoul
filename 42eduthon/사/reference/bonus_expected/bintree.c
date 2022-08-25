#include "bintree.h"

bintree	*make_bin_tree(bintree_node root_node)
{
	bintree			*tree;
	bintree_node	*p_root_node;

	tree = calloc(1, sizeof(bintree));
	p_root_node = calloc(1, sizeof(bintree_node));
	if (tree == NULL || p_root_node == NULL)
	{
		free(tree);
		free(p_root_node);
		return (NULL);
	}
	*p_root_node = root_node;
	tree->root_node = p_root_node;
	return (tree);
}

bintree_node	*get_root_node_bt(bintree *bintree)
{
	if (bintree == NULL)
		return (NULL);
	return (bintree->root_node);
}

bintree_node	*insert_left_child_node_bt(\
								bintree_node *parent_node, bintree_node element)
{
	bintree_node	*child;

	if (parent_node == NULL)
		return (NULL);
	if (parent_node->left_child)
	{
		printf("LeftChild Node already exist \n");
		return (NULL);
	}
	child = calloc(1, sizeof(bintree_node));
	if (child == NULL)
		return (NULL);
	*child = element;
	parent_node->left_child = child;
	return (child);
}

bintree_node	*insert_right_child_node_bt(\
								bintree_node *parent_node, bintree_node element)
{
	bintree_node	*child;

	if (parent_node == NULL)
		return (NULL);
	if (parent_node->right_child)
	{
		printf("RightChild Node already exist \n");
		return (NULL);
	}
	child = calloc(1, sizeof(bintree_node));
	if (child == NULL)
		return (NULL);
	*child = element;
	parent_node->right_child = child;
	return (child);
}
