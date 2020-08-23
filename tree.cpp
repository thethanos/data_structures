#include "tree.h"

#include <iostream>

void print_tree(Node* &pTree)
{
	if (pTree != nullptr)
	{
		print_tree(pTree->left);
		std::cout << pTree->m_Value << std::endl;
		print_tree(pTree->right);
	}
}

void add_node(int value, Node* &pTree)
{
	if (pTree == nullptr)
	{
		pTree = new Node();
		pTree->left = nullptr;
		pTree->m_Value = value;
		pTree->right = nullptr;
	}
	if (value < pTree->m_Value)
	{
		if (pTree->left != nullptr)
			add_node(value, pTree->left);
		else
		{
			pTree->left = new Node();
			pTree->left->left = nullptr;
			pTree->left->right = nullptr;
			pTree->left->m_Value = value;
		}
	}
	if (value > pTree->m_Value)
	{
		if (pTree->right != nullptr)
			add_node(value, pTree->right);
		else
		{
			pTree->right = new Node();
			pTree->right->left = nullptr;
			pTree->right->right = nullptr;
			pTree->right->m_Value = value;
		}
	}
}