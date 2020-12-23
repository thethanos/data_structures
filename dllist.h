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
		void push_front(T value);
		void pop_front();
		void push_back(T value);
		void pop_back();
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
	void DLList<T>::push_front(T value)
	{
		if (m_pHead == nullptr)
		{
			m_pHead = new Node<T>(value);
			m_pTail = m_pHead;
			m_Size++;
			return;
		}

		Node<T>* temp = m_pHead;
		m_pHead = new Node<T>(value);
		m_pHead->m_pNext = temp;
		temp->m_pPrev = m_pHead;
		m_Size++;
	}

	template <typename T>
	void DLList<T>::pop_front()
	{
		Node<T>* temp = m_pHead->m_pNext;
		if (temp)
			temp->m_pPrev = nullptr;

		delete m_pHead;
		m_pHead = temp;
		m_Size--;
	}

	template <typename T>
	void DLList<T>::push_back(T value)
	{
		if (m_pHead == nullptr)
		{
			m_pHead = new Node<T>(value);
			m_pTail = m_pHead;
			m_Size++;
			return;
		}

		Node<T>* temp = m_pTail;
		m_pTail->m_pNext = new Node<T>(value);
		m_pTail = m_pTail->m_pNext;
		m_pTail->m_pPrev = temp;
		m_Size++;
	}

	template <typename T>
	void DLList<T>::pop_back()
	{
		Node<T>* temp = m_pTail->m_pPrev;

		delete m_pTail;
		m_pTail = temp;
		if(m_pTail)
			m_pTail->m_pNext = nullptr;
		m_Size--;
	}
}