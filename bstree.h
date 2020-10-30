#pragma once

#include <iostream>

namespace BS
{
	template<typename T>
	class BSTree;

	template <typename T>
	class Node
	{
	public:
		Node(T value, Node<T>* parent = nullptr) :m_Value(value), m_pParent(parent) { }
		~Node() {};

	private:
		T	     m_Value;
		Node<T>* m_pParent{ nullptr };
		Node<T>* m_pLeft{ nullptr };
		Node<T>* m_pRight{ nullptr };

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
		void print() { print_node(m_pRoot); }

	private:
		Node<T>* m_pRoot;

	private:
		void insert_node(T value, Node<T>*& parent = nullptr);
		void print_node(Node<T>* node);
		void delete_node(Node<T>*& node);

		Node<T>* remove_node(T value, Node<T>*& node);
		Node<T>* find_min(Node<T>* node, Node<T>*& parent);
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
		if (node == nullptr) return;

		delete_node(node->m_pLeft);
		delete_node(node->m_pRight);

		delete node;
		node = nullptr;
	}

	template <typename T>
	Node<T>* BSTree<T>::remove_node(T value, Node<T>*& node)
	{
		if (value < node->m_Value)
			node->m_pLeft = remove_node(value, node->m_pLeft);

		if (value > node->m_Value)
			node->m_pRight = remove_node(value, node->m_pRight);

		if (value == node->m_Value)
		{
			Node<T>* left = node->m_pLeft;
			Node<T>* right = node->m_pRight;
			Node<T>* parent = node->m_pParent;

			if (right == nullptr) return left;

			Node<T>* min = find_min(right, node);

			min->m_pLeft = left;
			min->m_pRight = (min == right) ? right->m_pRight : right;
			min->m_pParent = parent;

			delete node;
			node = nullptr;

			if (m_pRoot == nullptr)
				return m_pRoot = min;

			return min;
		}

		return node;
	}

	template <typename T>
	Node<T>* BSTree<T>::find_min(Node<T>* node, Node<T>*& parent)
	{
		if (node->m_pLeft == nullptr)
		{
			parent->m_pLeft = node->m_pRight;
			return node;
		}

		return find_min(node->m_pLeft, node);
	}
}