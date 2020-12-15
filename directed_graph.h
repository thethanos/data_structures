#pragma once

#include <vector>
#include <set>
#include <iostream>
#include <list>

using std::vector;
using std::set;
using std::list;
using std::cout;
using std::endl;
using uint = unsigned int;

class DGraphAL
{
public:
	DGraphAL(uint size) { m_Data.resize(size); }

public:
	void add_vertex() { m_Data.push_back(set<uint>()); }
	void add_edge(uint from, uint to);
	void remove_edge(uint from, uint to);
	void print();

	bool is_edge(uint from, uint to);
	uint size() { return m_Data.size(); }

	void depth_first_search(uint vertex);
	void breadth_first_search(uint vertex);

private:
	void dfs_rec_func(uint vertex);

private:
	vector<set<uint>> m_Data;
	vector<uint>	  m_Visited;
};

void DGraphAL::add_edge(uint from, uint to)
{
	if (from >= m_Data.size() || to >= m_Data.size())
		return;

	if (is_edge(from, to))
		return;

	m_Data.at(from).insert(to);
}

void DGraphAL::remove_edge(uint from, uint to)
{
	if (from >= m_Data.size() || to >= m_Data.size())
		return;

	m_Data.at(from).erase(to);
}

void DGraphAL::print()
{
	for (uint vertex(0); vertex < m_Data.size(); ++vertex)
	{
		cout << "Vertex #" << vertex << " is adjacent to vertices: ";

		for (auto adj_vertex : m_Data[vertex])
			cout << adj_vertex << ' ';

		cout << endl;
	}
}

bool DGraphAL::is_edge(uint from, uint to)
{
	if (from >= m_Data.size() || to >= m_Data.size())
		return false;

	if(m_Data.at(from).count(to))
		return true;

	return false;
}

void DGraphAL::depth_first_search(uint vertex)
{
	m_Visited.resize(size(), 0);

	dfs_rec_func(vertex);
}

void DGraphAL::breadth_first_search(uint vertex)
{
	m_Visited.resize(size(), 0);
	m_Visited[vertex] = 1;

	list<uint> queue;
	queue.push_back(vertex);

	while (!queue.empty())
	{
		vertex = queue.front();
		queue.pop_front();

		cout << vertex << " ";

		for (auto vrtx : m_Data[vertex])
		{
			if (!m_Visited[vrtx])
			{
				m_Visited[vrtx] = 1;
				queue.push_back(vrtx);
			}
		}
	}
}

void DGraphAL::dfs_rec_func(uint vertex)
{
	m_Visited[vertex] = 1;

	cout << vertex << " ";

	for (auto vrtx : m_Data[vertex])
		if (!m_Visited[vrtx])
			dfs_rec_func(vrtx);
}

class DGraphAM
{
public:
	DGraphAM(uint size);

public:
	void add_edge(uint from, uint to);
	void remove_edge(uint from, uint to);
	void print();

	bool is_edge(uint from, uint to);
	uint size() { return m_Data.size(); }

	void depth_first_search(uint vertex);
	void breadth_first_search(uint vertex);

private:
	void dfs_rec_func(uint vertex);

private:
	vector<vector<uint>> m_Data;
	vector<uint>         m_Visited;
};

DGraphAM::DGraphAM(uint size)
{
	for (uint vertex(0); vertex < size; ++vertex)
		m_Data.push_back(vector<uint>(size));
}

void DGraphAM::add_edge(uint from, uint to)
{
	if (from >= m_Data.size() || to >= m_Data.size())
		return;

	m_Data[from][to] = 1;
}

void DGraphAM::remove_edge(uint from, uint to)
{
	if (from >= m_Data.size() || to >= m_Data.size())
		return;

	m_Data[from][to] = 0;
}

void DGraphAM::print()
{
	for (auto row : m_Data)
	{
		for (auto vertex : row)
			cout << vertex << ' ';
		cout << endl;
	}
}

bool DGraphAM::is_edge(uint from, uint to)
{
	if (from >= m_Data.size() || to >= m_Data.size())
		return false;

	if (m_Data[from][to])
		return true;

	return false;
}

void DGraphAM::depth_first_search(uint vertex)
{
	m_Visited.resize(size(), 0);

	dfs_rec_func(vertex);
}

void DGraphAM::breadth_first_search(uint vertex)
{
	m_Visited.resize(size(), 0);
	m_Visited[vertex] = 1;

	list<uint> queue;
	queue.push_back(vertex);

	while (!queue.empty())
	{
		vertex = queue.front();
		queue.pop_front();

		cout << vertex << " ";

		for (uint vrtx(0); vrtx < size(); ++vrtx)
		{
			if (!m_Data[vertex][vrtx])
				continue;

			if (!m_Visited[vrtx])
			{
				m_Visited[vrtx] = 1;
				queue.push_back(vrtx);
			}
		}
	}

}

void DGraphAM::dfs_rec_func(uint vertex)
{
	m_Visited[vertex] = 1;

	cout << vertex << " ";

	for (uint vrtx(0); vrtx < size(); ++vrtx)
	{
		if (!m_Data[vertex][vrtx])
			continue;

		if (!m_Visited[vrtx])
			dfs_rec_func(vrtx);
	}
}