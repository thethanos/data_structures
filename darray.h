#pragma once

using uint = unsigned int;

template <typename T>
class DArray
{
public:
	DArray() {}
	~DArray() {}

public:
	void push_back(T value);
	void pop_back() { m_Size--; }
	bool empty() { return m_Size == 0; }
	uint size()  { return m_Size; }
	T	 back()  { return m_pData[m_Size - 1]; }
	void resize(uint  size);

public:
	T& operator[](uint index) { return m_pData[index]; }

private:
	T*   m_pData{ nullptr };
	uint m_Size{ 0 };
	uint m_Capacity{ 0 };

public:
	using iterator = T*;
	iterator begin() { return m_pData; }
	iterator end()   { return m_pData + m_Size; }
};

template <typename T>
void DArray<T>::push_back(T value)
{
	if (m_pData == nullptr)
		resize(1);

	if (m_Size == m_Capacity)
		resize(m_Size);

	m_Size++;
	m_pData[m_Size - 1] = value;
}

template <typename T>
void DArray<T>::resize(uint size)
{
	m_Capacity = size * 2;

	T* temp = new T[m_Capacity];
	for (uint i(0); i < m_Size; i++)
		temp[i] = m_pData[i];

	m_Size = size;

	delete[] m_pData;
	m_pData = temp;
}
