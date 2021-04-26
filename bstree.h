#pragma once

#include <iostream>
#include <stack>

namespace BS
{
	template <typename T>
	struct Node
	{
		Node(T value, Node<T>* parent = nullptr) :m_Value(value), m_pParent(parent) { }
		~Node() {};

		T	     m_Value;
		Node<T>* m_pParent{ nullptr };
		Node<T>* m_pLeft{ nullptr };
		Node<T>* m_pRight{ nullptr };
	};
}

template <typename T>
class BSTree
{
public:
	BSTree() {}
	~BSTree() { delete_node(m_pRoot); }

public:
	void insert(const T& value) { insert_node(value, m_pRoot); }
	void remove(const T& value) { remove_node(value, m_pRoot); }

	size_t size() const  { return m_Size; }
	bool   empty() const { return !m_Size; }
	bool   contains(const T& value) const { return contains(value, m_pRoot); }

	BS::Node<T>* get_root() const { return m_pRoot; }

private:
	size_t		 m_Size = 0;
	BS::Node<T>* m_pRoot = nullptr;

private:
	void insert_node(const T& value, BS::Node<T>*& parent = nullptr);
	void delete_node(BS::Node<T>*& node);

	BS::Node<T>* remove_node(const T& value, BS::Node<T>*& node);
	BS::Node<T>* find_min(BS::Node<T>* node, BS::Node<T>*& parent);

	bool contains(const T& value, BS::Node<T>* node) const;
};

	template <typename T>
void BSTree<T>::insert_node(const T& value, BS::Node<T>*& node)
{
	if (!node)
	{
		node = new BS::Node<T>(value);
		m_Size++;
		return;
	}
	
	if (value < node->m_Value)
		insert_node(value, node->m_pLeft);
	
	if(value > node->m_Value)
		insert_node(value, node->m_pRight);
}

template <typename T>
void BSTree<T>::delete_node(BS::Node<T>*& node)
{
	if (node == nullptr) return;

	delete_node(node->m_pLeft);
	delete_node(node->m_pRight);

	delete node;
	node = nullptr;
	m_Size--;
}

template <typename T>
BS::Node<T>* BSTree<T>::remove_node(const T& value, BS::Node<T>*& node)
{
	if (!node) return nullptr;

	if (value < node->m_Value)
		node->m_pLeft = remove_node(value, node->m_pLeft);

	if (value > node->m_Value)
		node->m_pRight = remove_node(value, node->m_pRight);

	if (value == node->m_Value)
	{
		BS::Node<T>* left = node->m_pLeft;
		BS::Node<T>* right = node->m_pRight;
		BS::Node<T>* parent = node->m_pParent;

		if (right == nullptr)
		{
			m_Size--;
			return left;
		}

		BS::Node<T>* min = find_min(right, node);

		min->m_pLeft = left;
		min->m_pRight = (min == right) ? right->m_pRight : right;
		min->m_pParent = parent;

		delete node;
		node = nullptr;

		m_Size--;
		if (m_pRoot == nullptr)
			return m_pRoot = min;
		else
			return min;
	}

	return node;
}

template <typename T>
BS::Node<T>* BSTree<T>::find_min(BS::Node<T>* node, BS::Node<T>*& parent)
{
	if (node->m_pLeft == nullptr)
	{
		parent->m_pLeft = node->m_pRight;
		return node;
	}

	return find_min(node->m_pLeft, node);
}

template <typename T>
bool BSTree<T>::contains(const T& value, BS::Node<T>* node) const
{
	if (!node) return false;

	if (node->m_Value == value) return true;

	if (value < node->m_Value)
		return contains(value, node->m_pLeft);
	
	if (value > node->m_Value)
		return contains(value, node->m_pRight);

	return false;
}