#pragma once

#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

using uint = unsigned int;
using std::vector;
using std::set;
using std::cout;
using std::endl;

class UGraphAL
{
public:
	UGraphAL(uint size) { m_Data.resize(size); }

public:
	void add_vertex() { m_Data.push_back(set<uint>()); }
	void add_edge(uint from, uint to);
	void remove_edge(uint from, uint to);
	void print();

	bool is_edge(uint from, uint to);
	uint size() { return m_Data.size(); }

private:
	vector<set<uint>> m_Data;
};

void UGraphAL::add_edge(uint from, uint to)
{
	if (from >= m_Data.size() || to >= m_Data.size())
		return;

	if (is_edge(from, to))
		return;

	m_Data.at(from).insert(to);
	m_Data.at(to).insert(from);
}

void UGraphAL::remove_edge(uint from, uint to)
{
	if (!is_edge(from, to))
		return;
	
	m_Data.at(from).erase(to);
	m_Data.at(to).erase(from);
}

void UGraphAL::print()
{
	for (uint vertex(0); vertex < m_Data.size(); ++vertex)
	{
		cout << "Vertex #" << vertex << " is adjacent to vertices: ";

		for (auto adj_vertex : m_Data[vertex])
			cout << adj_vertex << ' ';

		cout << endl;
	}
}

bool UGraphAL::is_edge(uint from, uint to)
{
	if (from >= m_Data.size() || to >= m_Data.size())
		return false;

	if(m_Data.at(from).count(to))
		return true;

	return false;
}

class UGraphAM
{
public:
	UGraphAM(uint size);

public:
	void add_edge(uint from, uint to);
	void remove_edge(uint from, uint to);
	void print();

	bool is_edge(uint from, uint to);
	uint size() { return m_Data.size(); };

private:
	vector<vector<uint>> m_Data;
};

UGraphAM::UGraphAM(uint size)
{
	for (uint vertex(0); vertex < size; ++vertex)
		m_Data.push_back(vector<uint>(size));
}

void UGraphAM::add_edge(uint from, uint to)
{
	if (from >= m_Data.size() || to >= m_Data.size())
		return;

	m_Data[from][to] = 1;
	m_Data[to][from] = 1;
}

void UGraphAM::remove_edge(uint from, uint to)
{
	if (from >= m_Data.size() || to >= m_Data.size())
		return;

	m_Data[from][to] = 0;
	m_Data[to][from] = 0;
}

void UGraphAM::print()
{
	for (auto row : m_Data)
	{
		for (auto vertex : row)
			cout << vertex << ' ';
		cout << endl;
	}
}

bool UGraphAM::is_edge(uint from, uint to)
{
	if (from >= m_Data.size() || to >= m_Data.size())
		return false;

	if(m_Data[from][to] && m_Data[to][from])
		return true;

	return false;
}