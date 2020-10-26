#pragma once

#include <iostream>

enum COLORS
{
    RED = 0,
    BLACK
};

template <typename T>
class RBTree;

template <typename T>
class Node
{
public:
    Node(T value, bool color = RED, Node<T>* left = nullptr, Node<T>* right = nullptr, Node<T>* parent = nullptr);

private:
    T m_Value;

    Node<T>* m_pLeft;
    Node<T>* m_pRight;
    Node<T>* m_pParent;

    bool m_Color;

    friend RBTree<T>;
};

template <typename T>
Node<T>::Node(T value, bool color, Node<T>* left, Node<T>* right, Node<T>* parent)
{
    m_Value   = value;
    m_Color   = color;
    m_pLeft   = left;
    m_pRight  = right;
    m_pParent = parent;
}

template <typename T>
class RBTree
{
public:
    RBTree() { m_pNil = new Node<T>(-1, BLACK, m_pNil, m_pNil, m_pNil); m_pRoot = m_pNil; }

public:
    void insert(T value);
    void print() { print_node(m_pRoot); }

private:
    void rotate_left(Node<T>* x);
    void rotate_right(Node<T>* x);
    void print_node(Node<T>* node);

    Node<T>* insert_bst(Node<T>*& p, Node<T>*& node, T value);

private:
    Node<T>* m_pRoot;
    Node<T>* m_pNil;     //external node, color: black
};

template <typename T>
void RBTree<T>::rotate_left(Node<T>* node)
{
    Node<T>* newRoot = node->m_pRight;
    node->m_pRight = newRoot->m_pLeft;

    if (newRoot->m_pLeft != m_pNil)
        newRoot->m_pLeft->m_pParent = node;

    newRoot->m_pParent = node->m_pParent;

    if (node->m_pParent == m_pNil)
        m_pRoot = newRoot;
    else if (node->m_pParent->m_pLeft == node)
        node->m_pParent->m_pLeft = newRoot;
    else
        node->m_pParent->m_pRight = newRoot;

    node->m_pParent = newRoot;
    newRoot->m_pLeft = node;
}

template <typename T>
void RBTree<T>::rotate_right(Node<T>* node)
{
    Node<T>* newRoot = node->m_pLeft;
    node->m_pLeft = newRoot->m_pRight;

    if (newRoot->m_pRight != m_pNil)
        newRoot->m_pRight->m_pParent = node;

    newRoot->m_pParent = node->m_pParent;

    if (node->m_pParent == m_pNil)
        m_pRoot = newRoot;
    else if (node->m_pParent->m_pLeft == node)
        node->m_pParent->m_pLeft = newRoot;
    else
        node->m_pParent->m_pRight = newRoot;

    node->m_pParent = newRoot;
    newRoot->m_pRight = node;
}

template <typename T>
void RBTree<T>::print_node(Node<T>* node)
{
    if (node == m_pNil) return;

    print_node(node->m_pLeft);
    std::cout << "Value: " << node->m_Value << " color: " << (node->m_Color ? "black" : "red") << std::endl;
    print_node(node->m_pRight);
}

template <typename T>
Node<T>* RBTree<T>::insert_bst(Node<T>*& p, Node<T>*& node, T value)
{
    if (node == m_pNil)        //When the tree is empty
    {
        node = new Node<T>(value, RED, m_pNil, m_pNil, p);
        if (p == m_pNil)
            m_pRoot = node;
        if (value > p->m_Value)
            p->m_pRight = node;
        else
            p->m_pRight = node;
    }
    else                //tree is not empty
    {
        if (value < node->m_Value)
            return insert_bst(node, node->m_pLeft, value);
        else
            return insert_bst(node, node->m_pRight, value);
    }
    return node;
}

template <typename T>
void RBTree<T>::insert(T value)
{
    Node<T>* node = insert_bst(m_pNil, m_pRoot, value);
    // The following is insert_fixup, divided into 3x2 = 6 cases, from a symmetrical perspective, there are only three.
    while (node->m_pParent->m_Color == RED)
    {
        if (node->m_pParent->m_pParent->m_pLeft == node->m_pParent)
        {
            if (node->m_pParent->m_pParent->m_pRight->m_Color == RED)                //A: CASE 1
            {
                node->m_pParent->m_Color = BLACK;
                node->m_pParent->m_pParent->m_Color = RED;
                node->m_pParent->m_pParent->m_pRight->m_Color = BLACK;
                node = node->m_pParent->m_pParent;
            }
            else
            {
                if (node->m_pParent->m_pRight == node)                        //A: CASE 2
                {
                    node = node->m_pParent;
                    rotate_left(node);
                }                                           //A: CASE 3
                node->m_pParent->m_Color = BLACK;
                node->m_pParent->m_pParent->m_Color = RED;
                rotate_right(node->m_pParent->m_pParent);
            }
        }
        else
        {
            if (node->m_pParent->m_pParent->m_pLeft->m_Color == RED)                 //B: CASE 1
            {
                node->m_pParent->m_Color = BLACK;
                node->m_pParent->m_pParent->m_Color = RED;
                node->m_pParent->m_pParent->m_pLeft->m_Color = BLACK;
                node = node->m_pParent->m_pParent;
            }
            else
            {
                if (node->m_pParent->m_pLeft == node)                         //B: CASE 2
                {
                    node = node->m_pParent;
                    rotate_right(node);
                }
                node->m_pParent->m_Color = BLACK;                        //B: CASE 3
                node->m_pParent->m_pParent->m_Color = RED;
                rotate_left(node->m_pParent->m_pParent);

            }
        }
    }
    m_pRoot->m_Color = BLACK;                                   // Set the color of the root to BLACK
}