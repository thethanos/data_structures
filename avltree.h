#pragma once

#include <iostream>

namespace AVL
{
	template <typename T>
	class AVLTree;

	template <typename T>
	class Node
	{
	public:
		Node(T value) :m_Value(value) {}

	private:
		Node<T>* m_pLeft{ nullptr };
		Node<T>* m_pRight{ nullptr };

		T    m_Value;
		char m_Height{ 1 };

		friend AVLTree<T>;
	};

	template <typename T>
	class AVLTree
	{
	public:
		AVLTree() {}
		~AVLTree() { delete_node(m_pRoot); }

	public:
		void insert(T value) { insert_node(value, m_pRoot); }
		void remove(T value) { remove_node(value, m_pRoot); }
		void print() { print_node(m_pRoot); }


	private:
		void insert_node(T value, Node<T>*& node);
		void print_node(Node<T>* node);

		char get_height(Node<T>* node) { return node ? node->m_Height : 0; }
		char get_bfactor(Node<T>* node) { return get_height(node->m_pLeft) - get_height(node->m_pRight); }

		void fix_height(Node<T>*& node);

		Node<T>* rotate_right(Node<T>*& node);
		Node<T>* rotate_left(Node<T>*& node);
		Node<T>* balance_subtree(Node<T>*& node);
		Node<T>* find_min(Node<T>* node) { return node->m_pLeft ? find_min(node->m_pLeft) : node; }
		Node<T>* remove_min(Node<T>*& node);
		Node<T>* remove_node(T value, Node<T>*& node);

		void delete_node(Node<T>*& node);

	private:
		Node<T>* m_pRoot{ nullptr };
	};

	template <typename T>
	void AVLTree<T>::insert_node(T value, Node<T>*& node)
	{
		if (node == nullptr)
			node = new Node<T>(value);

		if (value < node->m_Value)
		{
			if (node->m_pLeft != nullptr)
				insert_node(value, node->m_pLeft);
			else
				node->m_pLeft = new Node<T>(value);
		}

		if (value > node->m_Value)
		{
			if (node->m_pRight != nullptr)
				insert_node(value, node->m_pRight);
			else
				node->m_pRight = new Node<T>(value);
		}

		node = balance_subtree(node);
	}

	template <typename T>
	Node<T>* AVLTree<T>::remove_node(T value, Node<T>*& node)
	{
		if (node == nullptr) return 0;

		if (value < node->m_Value)
			node->m_pLeft = remove_node(value, node->m_pLeft);

		if (value > node->m_Value)
			node->m_pRight = remove_node(value, node->m_pRight);

		if (value == node->m_Value)
		{
			Node<T>* left = node->m_pLeft;
			Node<T>* right = node->m_pRight;

			delete node;
			node = nullptr;

			if (right == nullptr) return left;

			Node<T>* min = find_min(right);
			min->m_pRight = remove_min(right);
			min->m_pLeft = left;

			if (m_pRoot == nullptr)
				return m_pRoot = balance_subtree(min);

			return balance_subtree(min);
		}

		return balance_subtree(node);
	}

	template <typename T>
	void AVLTree<T>::print_node(Node<T>* node)
	{
		if (node == nullptr) return;

		print_node(node->m_pLeft);
		std::cout << "Value: " << node->m_Value << " height: " << (int)node->m_Height << std::endl;
		print_node(node->m_pRight);
	}

	template <typename T>
	void AVLTree<T>::fix_height(Node<T>*& node)
	{
		char hleft = get_height(node->m_pLeft);
		char hright = get_height(node->m_pRight);

		node->m_Height = (hleft > hright ? hleft : hright) + 1;
	}

	template <typename T>
	Node<T>* AVLTree<T>::rotate_right(Node<T>*& node)
	{
		Node<T>* newRoot = node->m_pLeft;
		node->m_pLeft = newRoot->m_pRight;
		newRoot->m_pRight = node;

		fix_height(node);
		fix_height(newRoot);

		return newRoot;
	}

	template <typename T>
	Node<T>* AVLTree<T>::rotate_left(Node<T>*& node)
	{
		Node<T>* newRoot = node->m_pRight;
		node->m_pRight = newRoot->m_pLeft;
		newRoot->m_pLeft = node;

		fix_height(node);
		fix_height(newRoot);

		return newRoot;
	}

	template <typename T>
	Node<T>* AVLTree<T>::balance_subtree(Node<T>*& node)
	{
		fix_height(node);

		if (get_bfactor(node) == 2)
		{
			if (get_bfactor(node->m_pLeft) == -1)
				node->m_pLeft = rotate_left(node->m_pLeft);

			return rotate_right(node);
		}

		if (get_bfactor(node) == -2)
		{
			if (get_bfactor(node->m_pRight) == 1)
				node->m_pRight = rotate_right(node->m_pRight);

			return rotate_left(node);
		}

		return node;
	}

	template <typename T>
	Node<T>* AVLTree<T>::remove_min(Node<T>*& node)
	{
		if (node->m_pLeft == nullptr)
			return node->m_pRight;

		node->m_pLeft = remove_min(node->m_pLeft);
		return balance_subtree(node);
	}

	template <typename T>
	void AVLTree<T>::delete_node(Node<T>*& node)
	{
		if (node == nullptr) return;

		delete_node(node->m_pLeft);
		delete_node(node->m_pRight);

		delete node;
		node = nullptr;
	}
}