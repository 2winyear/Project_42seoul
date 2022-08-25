#include "bintree.h"

int main(void)
{	
	bintree			*tree;
	bintree_node	node;
	bintree_node	*first_left_node;
	bintree_node	*first_right_node;
	bintree_node	*second_left_node;
	bintree_node	*second_right_node;
	bintree_node	*second_left_node2;
	bintree_node	*second_right_node2;
	
	// Node
	node.data = 30;
	node.visited = 0;
	node.left_child = NULL;
	node.right_child = NULL;
	
	// Level 0: Tree - Root Node.
	tree = make_bin_tree(node); // A
	
	// Level 1
	node.data = 20;
	first_left_node = insert_left_child_node_bt(tree->root_node, node); // B
	node.data = 40;
	first_right_node = insert_right_child_node_bt(tree->root_node, node); // C
	
	// Level 2
	node.data = 10;
	second_left_node = insert_left_child_node_bt(first_left_node, node); // D
	node.data = 24;
	second_right_node = insert_right_child_node_bt(first_left_node, node); // E
	node.data = 34;
	second_left_node2 = insert_left_child_node_bt(first_right_node, node); // F
	node.data = 46;
	second_right_node2 = insert_right_child_node_bt(first_right_node, node); // G

	preorder(tree->root_node);
	printf("\n");
	inorder(tree->root_node);
	printf("\n");
	postorder(tree->root_node);
	printf("\n");
	delete_bintree(tree);
	// system("leaks a.out");
}
