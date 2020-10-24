#pragma once

#include <iostream>

template<typename T>
class BSTree;

template <typename T>
class Node
{
public:
	Node(T value, Node<T>* parent = nullptr):m_Value(value), m_pParent(parent) { }
	~Node() {};

private:
	T	     m_Value;
	Node<T>* m_pParent;
	Node<T>* m_pLeft;
	Node<T>* m_pRight;

	friend BSTree<T>;
};

template <typename T>
class BSTree
{
public:
	BSTree() {}
	~BSTree() { delete_node(m_pRoot); }

public:
	void insert(T value) { insert_node(value, m_pRoot); }
	void print()		 { print_node(m_pRoot); }

private:
	Node<T>* m_pRoot;

private:
	void insert_node(T value, Node<T>*& parent = nullptr);
	void print_node(Node<T>* node);
	void delete_node(Node<T>*& node);
};

template <typename T>
void BSTree<T>::insert_node(T value, Node<T>*& node)
{
	if (node == nullptr)
		node = new Node<T>(value);

	if (value < node->m_Value)
	{
		if (node->m_pLeft != nullptr)
			insert_node(value, node->m_pLeft);
		else
			node->m_pLeft = new Node<T>(value, node);
	}

	if (value > node->m_Value)
	{
		if (node->m_pRight != nullptr)
			insert_node(value, node->m_pRight);
		else
			node->m_pRight = new Node<T>(value, node);
	}
}

template <typename T>
void BSTree<T>::print_node(Node<T>* node)
{
	if (node == nullptr) return;

	print_node(node->m_pLeft);
	std::cout << node->m_Value << std::endl;
	print_node(node->m_pRight);
}

template <typename T>
void BSTree<T>::delete_node(Node<T>*& node)
{
	if (node == nullptr)
		return;

	delete_node(node->m_pLeft);
	delete_node(node->m_pRight);
	
	delete node;
	node = nullptr;
}
