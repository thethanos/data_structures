#pragma once

int HashFunctionHorner(const std::string& str, int size, int key)
{
	int result(0);
	for(int i(0); str[i] != 0; ++i)
		result = (key * result + str[i]) % size;

	result = (result * 2 + 1) % size;
	return result;
}

struct HashFunction1
{
	int operator()(const std::string& str, int size)
	{
		return HashFunctionHorner(str, size, size - 1);
	}
}

struct HashFunction2
{
	int operator()(const std::tring& str, int size)
	{
		return HashFunctionHorner(str, size, size + 1);
	}
}

template <typename T, typename THash1 = HashFunction1, typename THash2 = hashFunction2>
class HashTable
{
public:
	HashTable();
	~HashTable();

	static const int default_size = 8;
	constexpr static const double rehash_size = 0.75;

	struct Node
	{
		T value;
		bool state;
		Node(const T& value): value(value), state(true){}
	};

	Node** arr;
	int size;
	int buffer_size;
	int size_all_non_nullptr;

};
