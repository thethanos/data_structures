#pragma once


namespace DA
{
	template <typename T>
	class Allocator
	{
	public:
		static T*	allocate(size_t n); 
		static void	deallocate(T* ptr, size_t n = 0) noexcept { operator delete(ptr); }

		template <typename ... Args>
		static void construct(T* ptr, Args&& ... args)
		{
			try { new (ptr) T(std::forward<Args>(args)...); }
			catch (...) {}
		}
		static void destroy(T* ptr) noexcept { ptr->~T(); }
	};

	template <typename T>
	T* Allocator<T>::allocate(size_t n)
	{
		try{ return static_cast<T*>(operator new(n * sizeof(T))); }
		catch (...){}

		return nullptr;
	}
}

template <typename T, typename Allocator = DA::Allocator<T>>
class DArray
{
public:
	DArray() {}
	DArray(const DArray<T, Allocator>& other)  { *this = other; }
	DArray(DArray<T, Allocator>&& other) { *this = std::move(other); }
	DArray(const std::initializer_list<T>& lst);
	DArray(size_t size) { resize(size, T()); }
	~DArray();

public:
	void push_back(const T& value);
	void pop_back();

	template <typename ... Args>
	void emplace_back(Args&& ... args)
	{
		if (m_Size == 0)
			reserve(2);
		else if (m_Size == m_Capacity)
			reserve(m_Size * 2);

		m_Allocator.construct(m_pData + m_Size, std::forward<Args>(args)...);
		m_Size++;
	}

	bool   empty()	  const { return m_Size <= 0; }
	size_t size()	  const { return m_Size; }
	size_t capacity() const { return m_Capacity; }
	T&	   back()	  const { return m_pData[m_Size - 1]; }

	void resize(const size_t new_size);
	void resize(const size_t new_size, const T& value);
	void reserve(const size_t new_capacity);

public:
	T& operator[](size_t index) { return m_pData[index]; }

	DArray<T, Allocator>& operator=(const DArray<T, Allocator>& other);
	DArray<T, Allocator>& operator=(DArray<T, Allocator>&& other) noexcept;

private:
	T*     m_pData{ nullptr };
	size_t m_Size{ 0 };
	size_t m_Capacity{ 0 };

	Allocator m_Allocator;

public:
	using iterator = T*;
	iterator begin() const { return m_pData; }
	iterator end()   const { return m_pData + m_Size; }

	using value_type = T;
};

template <typename T, typename Allocator>
DArray<T, Allocator>::DArray(const std::initializer_list<T>& lst)
{
	m_pData = m_Allocator.allocate(lst.size());
	for (int i(0); i < lst.size(); ++i)
		m_Allocator.construct(m_pData + i, std::move(*(lst.begin() + i)));

	m_Size = m_Capacity = lst.size();
}

template <typename T, typename Allocator>
DArray<T, Allocator>::~DArray()
{
	for (int i(0); i < m_Size; ++i)
		m_Allocator.destroy(m_pData + i);

	m_Allocator.deallocate(m_pData, m_Capacity);
}

template <typename T, typename Allocator>
void DArray<T, Allocator>::push_back(const T& value)
{
	if(m_Size == 0) 
		reserve(2);
	else if(m_Size == m_Capacity) 
		reserve(m_Size * 2);

	m_Allocator.construct(m_pData+m_Size, value);
	m_Size++;
}

template <typename T, typename Allocator>
void DArray<T, Allocator>::pop_back()
{
	m_Allocator.destroy(m_pData + m_Size);
	m_Size--;
}

template <typename T, typename Allocator>
void DArray<T, Allocator>::resize(const size_t new_size)
{
	if(new_size <= 0) return;

	T* temp = m_Allocator.allocate(new_size);

	for (size_t i(0); i < m_Size; ++i)
		m_Allocator.construct(temp + i, *(m_pData + i));

	for (size_t i(m_Size); i < new_size; ++i)
		m_Allocator.construct(temp + i);

	for (size_t i(new_size); i < m_Size; ++i)
		m_Allocator.destroy(m_pData + i);

	m_Allocator.deallocate(m_pData, m_Capacity);

	m_Size = m_Capacity = new_size;
	m_pData = temp;
}

template <typename T, typename Allocator>
void DArray<T, Allocator>::resize(const size_t new_size, const T& value)
{
	if (new_size <= 0) return;

	size_t old_size = m_Size;
	resize(new_size);

	for (size_t i(old_size); i < new_size; ++i)
		m_pData[i] = value;
}

template <typename T, typename Allocator>
void DArray<T, Allocator>::reserve(size_t new_capacity)
{
	if(new_capacity <= 0 || new_capacity <= m_Size) return;

	T* temp = m_Allocator.allocate(new_capacity);

	for (int i(0); i < m_Size; ++i)
		m_Allocator.construct(temp + i, *(m_pData + i));

	m_Allocator.deallocate(m_pData, m_Capacity);

	m_Capacity = new_capacity;
	m_pData = temp;
}

template <typename T, typename Allocator>
DArray<T, Allocator>& DArray<T, Allocator>::operator=(const DArray<T, Allocator>& other)
{
	if (this == &other) return *this;

	resize(other.size());
	std::copy(other.begin(), other.end(), begin());

	return *this;
}

template <typename T, typename Allocator>
DArray<T, Allocator>& DArray<T, Allocator>::operator=(DArray<T, Allocator>&& other) noexcept
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