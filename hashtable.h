#pragma once

#include <vector>

using std::vector;

namespace HT 
{
	template <typename Key, typename Value>
	struct Bucket
	{
		Bucket(Key key, Value value = Value()) :m_Key(key), m_Value(value) {}

		Key   m_Key;
		Value m_Value;

		Bucket<Key, Value>* m_Next = nullptr;
	};
}

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable
{
public:
	HashTable(size_t size = 8) { m_Data.resize(size, nullptr); }

public:
	void insert(const std::pair<Key, Value>& pair);
	Value& operator[](const Key& key);

	size_t size() { return m_Size; }
	size_t bucket_count() { return m_Data.size(); }

private:
	vector<HT::Bucket<Key, Value>*> m_Data;
	Hash m_Hash;

	size_t m_Size = 0;

private:
	size_t get_index(const Key& key) { return m_Hash(key) % bucket_count(); }
	void   rehash();
};

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::insert(const std::pair<Key, Value>& pair)
{
	if (m_Size >= bucket_count())
		rehash();

	size_t index = get_index(pair.first);

	m_Data[index] = new HT::Bucket<Key, Value>(pair.first, pair.second);
	m_Size++;
}

template <typename Key, typename Value, typename Hash>
Value& HashTable<Key, Value, Hash>::operator[](const Key& key)
{
	size_t index = get_index(key);

	if (m_Data[index] == nullptr)
	{
		m_Data[index] = new HT::Bucket<Key, Value>(key);
		m_Size++;
	}

	return m_Data[index]->m_Value;
}

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::rehash()
{
	size_t old_count = bucket_count();
	m_Data.resize(old_count * 8, nullptr);
	
	Key temp_key;
	for (size_t i(0); i < old_count; ++i)
	{
		if (m_Data[i] != nullptr)
		{
			temp_key = m_Data[i]->m_Key;
			m_Data[get_index(temp_key)] = m_Data[i];
		}
	}
}