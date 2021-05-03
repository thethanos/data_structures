#pragma once

#include <algorithm>
#include "darray.h"

template <typename T, typename Container = DArray<T>, typename Comparator = std::less<T>>
class Heap
{
public:
    Heap() {}
    Heap(const std::initializer_list<T>& list);
    ~Heap(){}

public:
    void push(const T& value);
    void pop();
    T    top() { return m_Data[0]; }

    size_t size() const  { return m_Data.size(); }
    bool   empty() const { return m_Data.empty(); }

private:
    size_t parent(size_t index) const { return (index - 1) / 2; }
    size_t left_child(size_t index) const { return (2 * index) + 1; }
    size_t right_child(size_t index) const { return (2 * index) + 2; }

    void heapify(size_t index);

private:
    Container  m_Data;
    Comparator m_Compare;
};

template <typename T, typename Container, typename Comparator>
Heap<T, Container, Comparator>::Heap(const std::initializer_list<T>& list)
{
    m_Data.resize(list.size());
    std::copy(list.begin(), list.end(), m_Data.begin());

    for (int i = (m_Data.size() / 2) - 1; i >= 0; --i)
        heapify(i);
}

template <typename T, typename Container, typename Comparator>
void Heap<T, Container, Comparator>::push(const T& value)
{
    m_Data.push_back(value);

    size_t index = m_Data.size() - 1;
    while (index > 0 && m_Compare(m_Data[index], m_Data[parent(index)]))
    {
        std::swap(m_Data[parent(index)], m_Data[index]);
        index = parent(index);
    }
}

template <typename T, typename Container, typename Comparator>
void Heap<T, Container, Comparator>::pop()
{
    if (!size()) return;

    std::swap(m_Data[0], m_Data[size()-1]);
    m_Data.pop_back();

    heapify(0);
}

template <typename T, typename Container, typename Comparator>
void Heap<T, Container, Comparator>::heapify(size_t index)
{
    if (size() < 2) return;

    size_t left  = left_child(index);
    size_t right = right_child(index);
    size_t temp  = index;

    if (left < size() && m_Compare(m_Data[left], m_Data[index]))
        temp = left;

    if (right < size() && m_Compare(m_Data[right], m_Data[temp]))
        temp = right;

    if (temp != index)
    {
        std::swap(m_Data[index], m_Data[temp]);
        heapify(temp);
    }
}