#pragma once

#include <vector>

using std::vector;
using uint = unsigned int;

template <typename Key, typename Value>
class HashTable
{
public:
	HashTable(uint size) { m_Data.resize(size); }

public:
	Value& operator[](Key key) { return m_Data[hash_function(key)]; }

private:
	uint hash_function(Key key) { return reinterpret_cast<uint>(key) % m_Data.size(); }

private:
	vector<Value> m_Data;
};