#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_def.h"

typedef struct bintree_node_type
{
	char						data;
	int							visited;
	struct bintree_node_type	*left_child;
	struct bintree_node_type	*right_child;
}	bintree_node;

typedef struct bintree_type
{
	bintree_node	*root_node;
}	bintree;

bintree			*make_bin_tree(bintree_node root_node);
bintree_node	*get_root_node_bt(bintree *bintree);
bintree_node	*insert_left_child_node_bt(bintree_node *parent_node, \
														bintree_node element);
bintree_node	*insert_right_child_node_bt(bintree_node *parent_node, \
														bintree_node element);
bintree_node	*get_left_child_node_bt(bintree_node *node);
bintree_node	*get_right_child_node_bt(bintree_node *node);
void			delete_bintree(bintree *bintree);
void			delete_bintree_node(bintree_node **node);
void			preorder(bintree_node *tree_node);
void			inorder(bintree_node *tree_node);
void			postorder(bintree_node *tree_node);


