#pragma once

using uint = unsigned int;

namespace DLL
{
	template <typename T>
	class DLList;

	template <typename T>
	class Node
	{
	public:
		Node(T value, Node<T>* prev = nullptr):m_Value(value), m_pPrev(prev){}

	public:
		T m_Value;

	private:
		Node<T>* m_pPrev{nullptr};
		Node<T>* m_pNext{nullptr};

		friend DLList<T>;
	};

	template <typename T>
	class DLList
	{
	public:
		DLList() {}
		~DLList() {}

	public:
		void push_back(T value);
		void pop_front();
		uint size() { return m_Size; }
		bool empty() { return m_Size == 0; }
		T back()   { return m_pTail->m_Value; }
		T front()  { return m_pHead->m_Value; }

	private:
		Node<T>* m_pHead{nullptr};
		Node<T>* m_pTail{nullptr};

		uint m_Size{ 0 };
	};

	template <typename T>
	void DLList<T>::push_back(T value)
	{
		if (m_pHead == nullptr)
		{
			m_pHead = new Node<T>(value);
			m_Size++;
			return;
		}
		
		Node<T>* prev = m_pHead, *node = m_pHead->m_pNext;
		while (true)
		{
			if (node == nullptr)
			{
				node = new Node<T>(value, prev);
				prev->m_pNext = node;
				m_Size++;
				break;
			}

			prev = node;
			node = node->m_pNext;
		}

		m_pTail = node;
	}

	template <typename T>
	void DLList<T>::pop_front()
	{
		Node<T>* temp = m_pHead->m_pNext;
		if(temp)
			temp->m_pPrev = nullptr;

		delete m_pHead;
		m_pHead = temp;
		m_Size--;
	}
}