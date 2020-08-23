#include "tree.h"

int main(int argc, char** argv)
{
	Node* pTree = nullptr;

	add_node(10, pTree);
	add_node(11, pTree);
	add_node(8, pTree);
	add_node(2, pTree);
	add_node(1, pTree);
	add_node(12, pTree);


	print_tree(pTree);


	return 0;
}

