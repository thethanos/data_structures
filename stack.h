#pragma once

#include "darray.h"

template <typename T, typename Container = DArray<T>>
class Stack
{
public:
	Stack() {}
	~Stack() {}

public:
	void push(T value) { m_Data.push_back(value); }
	void pop() { m_Data.pop_back(); }
	T	 top() { return m_Data.back(); }
	bool empty() { return m_Data.empty(); }
	uint size() { return m_Data.size(); }

private:
	Container m_Data;
};