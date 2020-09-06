#pragma once

#include <deque>
#include <iostream>

template <typename T>
class Heap
{
	public:
		void Insert(T value);
		void Print();	
		T    ExtractMax();	

	private:
		void Heapify(int cur_item);	

	private:	
		std::deque<T> m_Data;
};

template <typename T>
void Heap<T>::Insert(T value)
{
	m_Data.push_back(value);
	int cur_item = m_Data.size() - 1;
        int parent   = (cur_item - 1)/2;
	
	while(cur_item > 0 && m_Data.at(parent) < m_Data.at(cur_item))
	{
		T temp 	         = m_Data[cur_item];
		m_Data[cur_item] = m_Data[parent];
		m_Data[parent]   = temp;

		cur_item = parent;
		parent   = (cur_item-1)/2;	
	}
}

template <typename T>
void Heap<T>::Print()
{
	for(auto item : m_Data)
	       std::cout << item << std::endl;	
}

template <typename T>
T Heap<T>::ExtractMax()
{
	T res = m_Data.front();
	m_Data[0] = m_Data.back();
	m_Data.pop_back();

	Heapify(0);
	return res;
}

template <typename T>
void Heap<T>::Heapify(int cur_item)
{
	int leftChild(0), rightChild(0), largestChild(0);

	while(true)
	{
		leftChild    = 2 * cur_item + 1;
		rightChild   = 2 * cur_item + 2;
		largestChild = cur_item;

		if(leftChild < m_Data.size() && m_Data.at(leftChild) > m_Data.at(rightChild))
			largestChild = leftChild;

		if(rightChild < m_Data.size() && m_Data.at(rightChild) > m_Data.at(leftChild))
			largestChild = rightChild;

		if(largestChild == cur_item)
			return;

		T temp 		     = m_Data[cur_item];
		m_Data[cur_item]     = m_Data[largestChild];
		m_Data[largestChild] = temp;
		cur_item 	     = largestChild;
	}
}


