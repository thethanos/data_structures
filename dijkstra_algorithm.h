#pragma once

#include <vector>

using std::vector;

class UGraph
{
public:
    UGraph(int order) { m_Data.resize(order, vector<int>(order)); }

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

void UGraph::add_edge(int from, int to, int weight)
{
    m_Data[from][to] = weight;
    m_Data[to][from] = weight;
}

void UGraph::dijkstra_algorithm(int start)
{
    m_Visited.resize(m_Data.size());
    m_Distances.resize(m_Data.size(), INT_MAX);
    m_Distances[start] = 0;

    int cur_vert(start);
    for (int vertex(0); vertex < m_Data.size(); ++vertex)
    {
        cur_vert = get_proximate_vertex();
        m_Visited[cur_vert] = true;

        for (int adj_vert(0); adj_vert < m_Data[vertex].size(); ++adj_vert)
        {
            if (m_Visited[adj_vert] || !m_Data[cur_vert][adj_vert]) continue;

            if (m_Distances[cur_vert] + m_Data[cur_vert][adj_vert] < m_Distances[adj_vert])
                m_Distances[adj_vert] = m_Distances[cur_vert] + m_Data[cur_vert][adj_vert];
        }
    }
}

int UGraph::get_proximate_vertex()
{
    int min_dist(INT_MAX);
    int min_index(0);

    for (int adj_vert(0); adj_vert < m_Data.size(); ++adj_vert)
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