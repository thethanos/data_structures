#pragma once

#include <vector>
#include <list>
#include <queue>

using std::vector;
using std::list;
using std::pair;
using std::priority_queue;


class UGraphAM
{
public:
    UGraphAM(size_t order) { m_Data.resize(order, vector<int>(order)); }

public:
    void add_edge(int from, int to, int weight);
    void dijkstra_algorithm(int start);

private:
    int get_proximate_vertex();

private:
    vector<vector<int>> m_Data;
    vector<bool>        m_Visited;
    vector<int>         m_Distances;
};

void UGraphAM::add_edge(int from, int to, int weight)
{
    m_Data[from][to] = weight;
    m_Data[to][from] = weight;
}

void UGraphAM::dijkstra_algorithm(int start)
{
    m_Visited.resize(m_Data.size());
    m_Distances.resize(m_Data.size(), INT_MAX);
    m_Distances[start] = 0;

    int cur_vert(start);
    for (size_t vertex(0); vertex < m_Data.size(); ++vertex)
    {
        cur_vert = get_proximate_vertex();
        m_Visited[cur_vert] = true;

        for (size_t adj_vert(0); adj_vert < m_Data[vertex].size(); ++adj_vert)
        {
            if (m_Visited[adj_vert] || !m_Data[cur_vert][adj_vert]) continue;

            if (m_Distances[cur_vert] + m_Data[cur_vert][adj_vert] < m_Distances[adj_vert])
                m_Distances[adj_vert] = m_Distances[cur_vert] + m_Data[cur_vert][adj_vert];
        }
    }
}

int UGraphAM::get_proximate_vertex()
{
    int min_dist(INT_MAX);
    int min_index(0);

    for (size_t adj_vert(0); adj_vert < m_Data.size(); ++adj_vert)
    {
        if (m_Visited[adj_vert]) continue;

        if (m_Distances[adj_vert] < min_dist)
        {
            min_dist = m_Distances[adj_vert];
            min_index = adj_vert;
        }
    }

    return min_index;
}

class UGraphAL
{
public:
    UGraphAL(size_t order) { m_Data.resize(order); }

public:
    void add_edge(int from, int to, int weight);
    void dijkstra_algorithm(int start);

private:
    vector<list<pair<int, int>>> m_Data;
    vector<int>                 m_Visited;
    vector<int>                 m_Distances;
};

void UGraphAL::add_edge(int from, int to, int weight)
{
    m_Data[from].push_back(pair{weight, to});
    m_Data[to].push_back(pair{ weight, from });
}

void UGraphAL::dijkstra_algorithm(int start)
{
    m_Distances.resize(m_Data.size(), INT_MAX);
    m_Visited.resize(m_Data.size());

    m_Distances[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> que;
    que.push(pair{ 0, start });

    int cur_vert(0);
    while (!que.empty())
    {
        cur_vert = que.top().second;
        que.pop();

        m_Visited[cur_vert] = true;

        for (auto adj_vert : m_Data[cur_vert])
        {
            if (m_Visited[adj_vert.second]) continue;

            if (m_Distances[cur_vert] + adj_vert.first < m_Distances[adj_vert.second])
            {
                m_Distances[adj_vert.second] = m_Distances[cur_vert] + adj_vert.first;
                adj_vert.first = m_Distances[cur_vert] + adj_vert.first;
                que.push(adj_vert);
            }
        }
    }
}