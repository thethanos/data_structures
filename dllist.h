#pragma once

using uint = unsigned int;


template <typename T>
class DLList;

namespace DLL
{
	template <typename T>
	class BidirectIterator;

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
		friend BidirectIterator<T>;
	};

	template <typename T>
	class BidirectIterator
	{
	public:
		BidirectIterator(Node<T>* pos = nullptr) :m_CurPos(pos) {}

	public:
		T& operator*() { return m_CurPos->m_Value; }

		BidirectIterator& operator++();
		BidirectIterator& operator--();

		BidirectIterator operator++(int);
		BidirectIterator operator--(int);

		bool operator==(BidirectIterator<T> other) { return m_CurPos == other.m_CurPos; }
		bool operator!=(BidirectIterator<T> other) { return m_CurPos != other.m_CurPos; }

	private:
		Node<T>* m_CurPos;
	};

	template <typename T>
	BidirectIterator<T>& BidirectIterator<T>::operator++()
	{
		if (!m_CurPos) return *this;

		m_CurPos = m_CurPos->m_pNext;
		return *this;
	}

	template <typename T>
	BidirectIterator<T>& BidirectIterator<T>::operator--()
	{
		if (!m_CurPos) return *this;

		m_CurPos = m_CurPos->m_pPrev;
		return *this;
	}

	template <typename T>
	BidirectIterator<T> BidirectIterator<T>::operator++(int)
	{
		if (!m_CurPos) return *this;

		Node<T>* temp = m_CurPos;
		m_CurPos = m_CurPos->m_pNext;
		return temp;
	}

	template <typename T>
	BidirectIterator<T> BidirectIterator<T>::operator--(int)
	{
		if (!m_CurPos) return *this;

		Node<T>* temp = m_CurPos;
		m_CurPos = m_CurPos->m_pNext;
		return temp;
	}
}

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
	uint size()  { return m_Size; }
	bool empty() { return m_Size == 0; }
	T back()     { return m_pTail->m_Value; }
	T front()    { return m_pHead->m_Value; }

private:
	DLL::Node<T>* m_pHead{nullptr};
	DLL::Node<T>* m_pTail{nullptr};

	uint m_Size{ 0 };

public:
	using iterator = DLL::BidirectIterator<T>;

	iterator begin() { return iterator(m_pHead); }
	iterator end()	 { return iterator(); }
};

template <typename T>
void DLList<T>::push_front(T value)
{
	if (m_pHead == nullptr)
	{
		m_pHead = new DLL::Node<T>(value);
		m_pTail = m_pHead;
		m_Size++;
		return;
	}

	DLL::Node<T>* temp = m_pHead;
	m_pHead = new DLL::Node<T>(value);
	m_pHead->m_pNext = temp;
	temp->m_pPrev = m_pHead;
	m_Size++;
}

template <typename T>
void DLList<T>::pop_front()
{
	DLL::Node<T>* temp = m_pHead->m_pNext;
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
		m_pHead = new DLL::Node<T>(value);
		m_pTail = m_pHead;
		m_Size++;
		return;
	}

	DLL::Node<T>* temp = m_pTail;
	m_pTail->m_pNext = new DLL::Node<T>(value);
	m_pTail = m_pTail->m_pNext;
	m_pTail->m_pPrev = temp;
	m_Size++;
}

template <typename T>
void DLList<T>::pop_back()
{
	DLL::Node<T>* temp = m_pTail->m_pPrev;

	delete m_pTail;
	m_pTail = temp;
	if(m_pTail)
		m_pTail->m_pNext = nullptr;
	m_Size--;
}