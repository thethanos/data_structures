#pragma once

#include <iostream>

template<typename T>
class Tree;

template <typename T>
class Node
{
public:
	Node(T data, Node<T>* pParent = nullptr);
	~Node() {};

private:
	T	     m_Data;
	Node<T>* m_pParent;
	Node<T>* m_pLeft;
	Node<T>* m_pRight;

	friend Tree;
};

template <typename T>
Node<T>::Node(T data, Node<T>* pParent)
{
	m_Data    = data;
	m_pParent = pParent;
	m_pLeft   = nullptr;
	m_pRight  = nullptr;
}

template <typename T>
class Tree
{
public:
	Tree(T value);
	~Tree() {}

public:
	void Insert(T value) { AddNode(value, m_pRoot); }
	void Print()		 { PrintNode(m_pRoot); }

private:
	Node<T>* m_pRoot;

private:
	void AddNode(T value, Node<T>* &pParent = nullptr);
	void PrintNode(Node<T>* current_node);
};

template <typename T>
Tree<T>::Tree(T value)
{
	m_pRoot = new Node(value);
}

template <typename T>
void Tree<T>::AddNode(T value, Node<T>* &current_node)
{
	if (current_node == nullptr)
		current_node = new Node(value);

	if (value < current_node->m_Data)
	{
		if (current_node->m_pLeft != nullptr)
			AddNode(value, current_node->m_pLeft);
		else
			current_node->m_pLeft = new Node(value, current_node);
	}

	if (value > current_node->m_Data)
	{
		if (current_node->m_pRight != nullptr)
			AddNode(value, current_node->m_pRight);
		else
			current_node->m_pRight = new Node(value, current_node);
	}
}

template <typename T>
void Tree<T>::PrintNode(Node<T>* current_node)
{
	if (current_node != nullptr)
	{
		PrintNode(current_node->m_pLeft);
		std::cout << current_node->m_Data << std::endl;
		PrintNode(current_node->m_pRight);
	}
}