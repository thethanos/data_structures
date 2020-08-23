#pragma once

struct Node
{
	int m_Value;
	Node *left, *right;
};

void print_tree(Node* &pTree);
void add_node(int value, Node* &pTree);

