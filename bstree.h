#pragma once

#include <iostream>

template<typename T>
class BSTree;

template <typename T>
class Node
{
public:
	Node(T value, Node<T>* pParent = nullptr) :m_Value(value), m_pParent(pParent) {}
	~Node() {};

private:
	T	     m_Value;
	Node<T>* m_pParent{nullptr};
	Node<T>* m_pLeft{nullptr};
	Node<T>* m_pRight{nullptr};

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
	void remove(T value) { remove_node(value, m_pRoot); }
	void print()		 { print_node(m_pRoot); }

private:
	Node<T>* m_pRoot;

private:
	void	 insert_node(T value, Node<T>*& pParent = nullptr);
	Node<T>* remove_node(T value, Node<T>*& node);
	Node<T>* find_min(Node<T>* node);

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
Node<T>* BSTree<T>::remove_node(T value, Node<T>*& node)
{
	if (value < node->m_Value)
		remove_node(value, node->m_pLeft);

	if (value > node->m_Value)
		remove_node(value, node->m_pRight);

	if (value == node->m_Value)
	{
		Node<T>* min = find_min(node->m_pRight);

		delete node;
		node = nullptr;
	}

	return node;
}

template <typename T>
Node<T>* BSTree<T>::find_min(Node<T>* node)
{
	if (node->m_pLeft == nullptr) return node;
	
	return find_min(node->m_pLeft);
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
	if (node == nullptr) return;

	delete_node(node->m_pLeft);
	delete_node(node->m_pRight);
	
	delete node;
	node = nullptr;
}
