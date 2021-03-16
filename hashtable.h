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
	size_t get_index(const Key& key, int count) { return m_Hash(key) % count; }
	void   rehash();
};

template <typename Key, typename Value, typename Hash>
void HashTable<Key, Value, Hash>::insert(const std::pair<Key, Value>& pair)
{
	if (m_Size >= bucket_count())
		rehash();

	size_t index = get_index(pair.first, bucket_count());

	m_Data[index] = new HT::Bucket<Key, Value>(pair.first, pair.second);
	m_Size++;
}

template <typename Key, typename Value, typename Hash>
Value& HashTable<Key, Value, Hash>::operator[](const Key& key)
{
	size_t index = get_index(key, bucket_count());

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
	
	int new_index = 0;
	vector<HT::Bucket<Key, Value>*> temp(old_count *8, nullptr);
	for (int i(0); i < old_count; ++i)
	{
		if (m_Data[i] == nullptr) continue;

		new_index		= get_index(m_Data[i]->m_Key, temp.size());
		temp[new_index] = m_Data[i];
	}

	m_Data = std::move(temp);
}