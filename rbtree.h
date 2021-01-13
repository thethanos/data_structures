#pragma once

#include <iostream>

namespace RB
{
    enum COLOR
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
        Node(T value, COLOR color = RED, Node<T>* left = nullptr, Node<T>* right = nullptr, Node<T>* parent = nullptr);

        T m_Value;

        Node<T>* m_pLeft;
        Node<T>* m_pRight;
        Node<T>* m_pParent;

        COLOR m_Color;

        Node<T>* get_grandparent() { return m_pParent->m_pParent; };
    };

    template <typename T>
    Node<T>::Node(T value, COLOR color, Node<T>* parent, Node<T>* left, Node<T>* right)
    {
        m_Value = value;
        m_Color = color;
        m_pParent = parent;
        m_pLeft = left;
        m_pRight = right;
    }
}

template <typename T>
class RBTree
{
public:
    RBTree() { m_pNil = new RB::Node<T>(-1, RB::BLACK, m_pNil, m_pNil, m_pNil); m_pRoot = m_pNil; }

public:
    void insert(T value);
    void remove(T value) { remove_node(find_node(value, m_pRoot)); }
    void print() { print_node(m_pRoot); }

private:
    void rotate_left(RB::Node<T>* node);
    void rotate_right(RB::Node<T>* node);
    void swap_colors(RB::Node<T>* node);
    void print_node(RB::Node<T>* node);
    void rb_transplant(RB::Node<T>*& first, RB::Node<T>*& second);
    void remove_node(RB::Node<T>* node);
    void balance_after_remove(RB::Node<T>* node);

    RB::Node<T>* insert_node(T value, RB::Node<T>*& node);
    RB::Node<T>* find_min(RB::Node<T>* node);
    RB::Node<T>* find_node(T value, RB::Node<T>* node);

private:
    RB::Node<T>* m_pRoot;
    RB::Node<T>* m_pNil;
};

template <typename T>
void RBTree<T>::rotate_left(RB::Node<T>* node)
{
    RB::Node<T>* newRoot = node->m_pRight;
    node->m_pRight = newRoot->m_pLeft;

    if (newRoot->m_pLeft != m_pNil)
        newRoot->m_pLeft->m_pParent = node;

    newRoot->m_pParent = node->m_pParent;

    if (node->m_pParent == m_pNil)
        m_pRoot = newRoot;
    else
    {
        if (node->m_pParent->m_pLeft == node)
            node->m_pParent->m_pLeft = newRoot;
        else
            node->m_pParent->m_pRight = newRoot;
    }

    node->m_pParent = newRoot;
    newRoot->m_pLeft = node;
}

template <typename T>
void RBTree<T>::rotate_right(RB::Node<T>* node)
{
    RB::Node<T>* newRoot = node->m_pLeft;
    node->m_pLeft = newRoot->m_pRight;

    if (newRoot->m_pRight != m_pNil)
        newRoot->m_pRight->m_pParent = node;

    newRoot->m_pParent = node->m_pParent;

    if (node->m_pParent == m_pNil)
        m_pRoot = newRoot;
    else
    {
        if (node->m_pParent->m_pLeft == node)
            node->m_pParent->m_pLeft = newRoot;
        else
            node->m_pParent->m_pRight = newRoot;
    }

    node->m_pParent = newRoot;
    newRoot->m_pRight = node;
}

template <typename T>
void RBTree<T>::swap_colors(RB::Node<T>* node)
{
    node->m_pParent->m_Color = RB::BLACK;
    node->get_grandparent()->m_Color = RB::RED;
}

template <typename T>
void RBTree<T>::print_node(RB::Node<T>* node)
{
    if (node == m_pNil) return;

    print_node(node->m_pLeft);
    std::cout << "Value: " << node->m_Value << " color: " << (node->m_Color ? "black" : "red") << std::endl;
    print_node(node->m_pRight);
}

template <typename T>
RB::Node<T>* RBTree<T>::insert_node(T value, RB::Node<T>*& node) 
{
    if (node == m_pNil)
        node = new RB::Node<T>(value, RB::RED, m_pNil, m_pNil, m_pNil);

    if (value < node->m_Value)
    {
        if (node->m_pLeft == m_pNil)
            return node->m_pLeft = new RB::Node<T>(value, RB::RED, node, m_pNil, m_pNil);
        else
            return insert_node(value, node->m_pLeft);
    }

    if (value > node->m_Value)
    {
        if (node->m_pRight == m_pNil)
            return node->m_pRight = new RB::Node<T>(value, RB::RED, node, m_pNil, m_pNil);
        else
            return insert_node(value, node->m_pRight);
    }

    return node;
}

template <typename T>
void RBTree<T>::insert(T value)
{
    RB::Node<T>* node = insert_node(value, m_pRoot);

    while (node->m_pParent->m_Color == RB::RED)
    {
        if (node->get_grandparent()->m_pLeft == node->m_pParent)
        {
            if (node->get_grandparent()->m_pRight->m_Color == RB::RED)
            {
                swap_colors(node);
                node->get_grandparent()->m_pRight->m_Color = RB::BLACK;
                node = node->get_grandparent();
            }
            else
            {
                if (node->m_pParent->m_pRight == node)
                {
                    node = node->m_pParent;
                    rotate_left(node);
                }

                swap_colors(node);
                rotate_right(node->get_grandparent());
            }
        }
        else
        {
            if (node->get_grandparent()->m_pLeft->m_Color == RB::RED)
            {
                swap_colors(node);
                node->get_grandparent()->m_pLeft->m_Color = RB::BLACK;
                node = node->get_grandparent();
            }
            else
            {
                if (node->m_pParent->m_pLeft == node)
                {
                    node = node->m_pParent;
                    rotate_right(node);
                }

                swap_colors(node);
                rotate_left(node->get_grandparent());
            }
        }
    }
    m_pRoot->m_Color = RB::BLACK;
}

template <typename T>
RB::Node<T>* RBTree<T>::find_min(RB::Node<T>* node)
{
    RB::Node<T>* temp = node;
    while (node != m_pNil)
    {
        temp = node;
        node = node->m_pLeft;
    }
    return temp;
}

template <typename T>
void RBTree<T>::rb_transplant(RB::Node<T>*& first, RB::Node<T>*& second)
{
    if (first->m_pParent == m_pNil)
        m_pRoot = second;
    else if (first == first->m_pParent->m_pLeft)
        first->m_pParent->m_pLeft = second;
    else
        first->m_pParent->m_pRight = second;

    second->m_pParent = first->m_pParent;
}

template <typename T>
void RBTree<T>::remove_node(RB::Node<T>* node)
{
    RB::Node<T>* y = node;
    bool delcol = y->m_Color;
    RB::Node<T>* x = node;

    if (node->m_pLeft == m_pNil)
    {
        x = node->m_pRight;
        rb_transplant(node, node->m_pRight);
    }
    else if (node->m_pRight == m_pNil)
    {
        x = node->m_pLeft;
        rb_transplant(node, node->m_pLeft);
    }
    else
    {
        y = find_min(node->m_pRight);
        delcol = y->m_Color;
        x = y->m_pRight;
        if (y->m_pParent == node)
        {
            x->m_pParent = y;
        }
        else
        {
            rb_transplant(y, y->m_pRight);
            y->m_pRight = node->m_pRight;
            y->m_pRight->m_pParent = y;
        }

        rb_transplant(node, y);
        y->m_pLeft = node->m_pLeft;
        y->m_pLeft->m_pParent = y;
        y->m_Color = node->m_Color;
    }

    if (delcol == RB::BLACK)
        balance_after_remove(x);
}

template <typename T>
void RBTree<T>::balance_after_remove(RB::Node<T>* x)
{
    while (x != m_pRoot && x->m_Color == RB::BLACK)
    {
        if (x == x->m_pParent->m_pLeft)
        {
            RB::Node<T>* w = x->m_pParent->m_pRight;
            if (w->m_Color == RB::RED)                                       //A: CASE 1
            {
                w->m_Color = RB::BLACK;
                x->m_pParent->m_Color = RB::RED;
                rotate_left(x->m_pParent);
                w = x->m_pParent->m_pRight;
            }
            if (w->m_pLeft->m_Color == RB::BLACK and w->m_pRight->m_Color == RB::BLACK)    //A: CASE 2
            {
                w->m_Color = RB::RED;
                x = x->m_pParent;
            }
            else
            {
                if (w->m_pRight->m_Color == RB::BLACK)                           //A: CASE 3
                {
                    w->m_pLeft->m_Color = RB::BLACK;
                    w->m_Color = RB::RED;
                    rotate_right(w);
                    w = x->m_pParent->m_pRight;
                }

                w->m_Color = x->m_pParent->m_Color;                                 //A: CASE 4
                x->m_pParent->m_Color = RB::BLACK;
                w->m_pRight->m_Color = RB::BLACK;

                rotate_left(x->m_pParent);
                x = m_pRoot;
            }
        }
        else
        {
            RB::Node<T>* w = x->m_pParent->m_pLeft;
            if (w->m_Color == RB::RED)                                         //B: CASE 1
            {
                w->m_Color = RB::BLACK;
                x->m_pParent->m_Color = RB::RED;
                rotate_right(x->m_pParent);
                w = x->m_pParent->m_pLeft;
            }
            if (w->m_pRight->m_Color == RB::BLACK && w->m_pLeft->m_Color == RB::RED)           //B: CASE 2
            {
                w->m_Color = RB::RED;
                x = x->m_pParent;
            }
            else
            {
                if (w->m_pLeft->m_Color == RB::BLACK)                             //B: CASE 3
                {
                    w->m_pRight->m_Color = RB::BLACK;
                    w->m_Color = RB::RED;
                    rotate_left(w);
                    w = x->m_pParent->m_pLeft;
                }

                w->m_Color = x->m_pParent->m_Color;                                 //B: CASE 4
                x->m_pParent->m_Color = RB::BLACK;
                w->m_pLeft->m_Color = RB::BLACK;

                rotate_right(x->m_pParent);
                x = m_pRoot;
            }
        }
    }
    x->m_Color = RB::BLACK;
}

template <typename T>
RB::Node<T>* RBTree<T>::find_node(T value, RB::Node<T>* node)
{
    if (value == node->m_Value) return node;

    if (value < node->m_Value)
        return find_node(value, node->m_pLeft);

    if (value > node->m_Value)
        return find_node(value, node->m_pRight);

    return node;
}