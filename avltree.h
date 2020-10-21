#pragma once

#include <iostream>

template <typename T>
struct Node
{
	Node(T value, Node<T>* parent) :m_value(value), m_parent(parent){}

	Node<T>* m_left{nullptr};
	Node<T>* m_right{ nullptr };
	Node<T>* m_parent{ nullptr };

	T m_value;

	int m_height{ 1 };
};

template <typename T>
void insert(T value, Node<T>*& node, Node<T>* parent = nullptr)
{
	if (!node)
	{
		node = new Node<T>(value, parent);
		return;
	}

	if (value < node->m_value)
		insert(value, node->m_left);
	else if(value > node->m_value)
		insert(value, node->m_right);

	node = balance_subtree(node);
}

template <typename T>
void print(Node<T>* node)
{
	if (!node) return;

	print(node->m_left);
	std::cout << "Value: " << node->m_value << " height: " << node->m_height << std::endl;
	print(node->m_right);
}

template <typename T>
int get_height(Node<T>* node)
{
	return node ? node->m_height : 0;
}

template <typename T>
int get_bfactor(Node<T>* node)
{
	return get_height(node->m_left) - get_height(node->m_right);
}

template <typename T>
void fix_height(Node<T>*& node)
{
	int hleft  = get_height(node->m_left);
	int hright = get_height(node->m_right);

	node->m_height = (hleft > hright?hleft:hright) + 1;
}

template <typename T>
Node<T>* rotate_right(Node<T>*& node)
{
	Node<T>* newRoot = node->m_left;
	node->m_left	 = newRoot->m_right;
	newRoot->m_right = node;
	
	return newRoot;
}

template <typename T>
Node<T>* rotate_left(Node<T>*& node)
{
	Node<T>* newRoot = node->m_right;
	node->m_right	 = newRoot->m_left;
	newRoot->m_left	 = node;

	return newRoot;
}

template <typename T>
Node<T>* balance_subtree(Node<T>*& node)
{
	fix_height(node);

	if (get_bfactor(node) == 2)
	{
		if (get_bfactor(node->m_left) == -1)
			node->m_left = rotate_left(node->m_left);

		return rotate_right(node);
	}

	if (get_bfactor(node) == -2)
	{
		if (get_bfactor(node->m_right) == 1)
			node->m_right = rotate_right(node->m_right);

		return rotate_left(node);
	}

	return node;
}