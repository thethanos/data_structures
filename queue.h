#pragma once

#include "dllist.h"

template <typename T, typename Container = DLList<T>>
class Queue
{
public:
	Queue() {}
	~Queue() {}

public:
	void push(T value) { m_Data.push_back(value); }
	void pop()   { m_Data.pop_front();    }
	bool empty() { return m_Data.empty(); }
	uint size()  { return m_Data.size();  }
	T front()    { return m_Data.front(); }
	T back()     { return m_Data.back();  }

private:
	Container m_Data;
};