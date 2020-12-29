#pragma once

#include "darray.h"
#include "sorting_algorithms.h"

using util::swap;


template <typename T, typename Container = DArray<T>, typename Comparator = std::less<T>>
class Heap
{
public:
    void push(T value);
    void pop();
    T    top() { return m_Data[0]; }

private:
    uint parent(uint index) { return (index - 1) / 2; }
    uint left_child(uint index) { return (2 * index) + 1; }
    uint right_child(uint index) { return (2 * index) + 2; }

    void heapify(uint index);

private:
    Container  m_Data;
    Comparator m_Compare;
};

template <typename T, typename Container, typename Comparator>
void Heap<T, Container, Comparator>::push(T value)
{
    m_Data.push_back(value);

    int index = m_Data.size() - 1;
    while (index != 0 && m_Compare(m_Data[index], m_Data[parent(index)]))
    {
        swap(m_Data[parent(index)], m_Data[index]);
        index = parent(index);
    }
}

template <typename T, typename Container, typename Comparator>
void Heap<T, Container, Comparator>::pop()
{
    if (m_Data.empty()) return;

    int last = m_Data.size() - 1;

    m_Data[0] = m_Data[last];
    m_Data.pop_back();

    heapify(0);
}

template <typename T, typename Container, typename Comparator>
void Heap<T, Container, Comparator>::heapify(uint index)
{
    if (m_Data.empty()) return;

    int left = left_child(index);
    int right = right_child(index);
    int temp = index;

    if (left < m_Data.size() && m_Compare(m_Data[left], m_Data[index]))
        temp = left;

    if (right < m_Data.size() && m_Compare(m_Data[right], m_Data[temp]))
        temp = right;

    if (temp != index)
    {
        swap(m_Data[index], m_Data[temp]);
        heapify(temp);
    }
}