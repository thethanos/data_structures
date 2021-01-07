#pragma once

#include <algorithm>


template <typename T>
class DArray
{
public:
	DArray() {}
	DArray(DArray<T>& other)  { *this = other; }
	DArray(DArray<T>&& other) { *this = std::move(other); }
	DArray(const std::initializer_list<T>& lst);
	DArray(size_t size) { resize(size, T()); }
	~DArray() { delete[] m_pData; }

public:
	void push_back(const T& value);
	void pop_back() { --m_Size; }

	bool   empty()	  const { return m_Size <= 0; }
	size_t size()	  const { return m_Size; }
	size_t capacity() const { return m_Capacity; }
	T&	   back()	  const { return m_pData[m_Size - 1]; }

	void resize(const size_t new_size);
	void resize(const size_t new_size, const T value);
	void reserve(const size_t new_capacity);

public:
	T& operator[](size_t index) { return m_pData[index]; }

	DArray<T>& operator=(DArray<T>& other);
	DArray<T>& operator=(DArray<T>&& other);

private:
	T*     m_pData{ nullptr };
	size_t m_Size{ 0 };
	size_t m_Capacity{ 0 };

public:
	using iterator = T*;
	iterator begin() const { return m_pData; }
	iterator end()   const { return m_pData + m_Size; }

	using value_type = T;
};

template <typename T>
DArray<T>::DArray(const std::initializer_list<T>& lst)
{
	resize(lst.size());
	std::copy(lst.begin(), lst.end(), begin());
}

template <typename T>
void DArray<T>::push_back(const T& value)
{
	if(m_Size == 0) 
		reserve(2);
	else if(m_Size == m_Capacity) 
		reserve(m_Size * 2);

	m_pData[m_Size] = value;
	m_Size++;
}

template <typename T>
void DArray<T>::resize(const size_t new_size)
{
	if(new_size <= 0) return;

	T* temp = new T[new_size];

	if(m_pData)
		std::copy(begin(), end(), temp);

	m_Size = m_Capacity = new_size;
	delete[] m_pData;
	m_pData = temp;
}

template <typename T>
void DArray<T>::resize(size_t new_size, T value)
{
	if(new_size <= 0) return;

	size_t old_size = m_Size;
	resize(new_size);

	for(size_t counter(old_size); counter < m_Size; ++counter)
		m_pData[counter] = value;
}

template <typename T>
void DArray<T>::reserve(size_t new_capacity)
{
	if(new_capacity <= 0 || new_capacity <= m_Size) return;

	if (new_capacity <= m_Capacity)
	{
		m_Capacity = new_capacity;
		return;
	}

	T* temp = new T[new_capacity];

	if(m_pData)
		std::copy(begin(), end(), temp);

	m_Capacity = new_capacity;
	delete[] m_pData;
	m_pData = temp;
}

template <typename T>
DArray<T>& DArray<T>::operator=(DArray<T>& other)
{
	if (this == &other) return *this;

	resize(other.size());
	std::copy(other.begin(), other.end(), begin());

	return *this;
}

template <typename T>
DArray<T>& DArray<T>::operator=(DArray<T>&& other)
{
	if (this == &other) return *this;

	m_Size = other.m_Size;
	m_Capacity = other.m_Capacity;
	m_pData = other.m_pData;

	other.m_Size = 0;
	other.m_Capacity = 0;
	other.m_pData = nullptr;

	return *this;
}