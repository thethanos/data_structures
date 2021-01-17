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

    vector<int> get_path(int from, int to);

private:
    int  get_closest_vertex();
    void get_path(vector<int>& path, int to);

private:
    vector<vector<int>> m_Data;
    vector<bool>        m_Visited;
    vector<int>         m_Distances;
    vector<int>         m_Path;
};

void UGraphAM::add_edge(int from, int to, int weight)
{
    m_Data[from][to] = weight;
    m_Data[to][from] = weight;
}

void UGraphAM::dijkstra_algorithm(int start)
{
    m_Visited.clear();
    m_Distances.clear();
    m_Path.clear();

    m_Visited.resize(m_Data.size());
    m_Distances.resize(m_Data.size(), INT_MAX);
    m_Path.resize(m_Data.size(), -1);

    m_Distances[start] = 0;

    int cur_vert(start);
    for (size_t vertex(0); vertex < m_Data.size(); ++vertex)
    {
        cur_vert = get_closest_vertex();
        m_Visited[cur_vert] = true;

        for (size_t adj_vert(0); adj_vert < m_Data[vertex].size(); ++adj_vert)
        {
            if (m_Visited[adj_vert] || !m_Data[cur_vert][adj_vert]) continue;

            if (m_Distances[cur_vert] + m_Data[cur_vert][adj_vert] < m_Distances[adj_vert])
            {
                m_Path[adj_vert] = cur_vert;
                m_Distances[adj_vert] = m_Distances[cur_vert] + m_Data[cur_vert][adj_vert];
            }
        }
    }
}

vector<int> UGraphAM::get_path(int from, int to)
{
    vector<int> path;
    dijkstra_algorithm(from);

    path.push_back(from);
    get_path(path, to);

    return path;
}

int UGraphAM::get_closest_vertex()
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

void UGraphAM::get_path(vector<int>& path, int to)
{
    if (m_Path[to] == -1)
        return;

    get_path(path, m_Path[to]);

    path.push_back(to);
}

class UGraphAL
{
public:
    UGraphAL(size_t order) { m_Data.resize(order); }

public:
    void add_edge(int from, int to, int weight);
    void dijkstra_algorithm(int start);

    vector<int> get_path(int from, int to);

private:
    void get_path(vector<int>& path, int index);

private:
    vector<list<pair<int, int>>> m_Data;
    vector<bool>                 m_Visited;
    vector<int>                  m_Distances;
    vector<int>                  m_Path;
};

void UGraphAL::add_edge(int from, int to, int weight)
{
    m_Data[from].push_back(std::make_pair(weight, to));
    m_Data[to].push_back(std::make_pair(weight, from));
}

void UGraphAL::dijkstra_algorithm(int start)
{   
    m_Distances.clear();
    m_Visited.clear();
    m_Path.clear();

    m_Distances.resize(m_Data.size(), INT_MAX);
    m_Visited.resize(m_Data.size());
    m_Path.resize(m_Data.size(), -1);

    m_Distances[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> que;
    que.push(std::make_pair( 0, start ));

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
                m_Path[adj_vert.second] = cur_vert;
                m_Distances[adj_vert.second] = m_Distances[cur_vert] + adj_vert.first;
                que.push(std::make_pair(m_Distances[adj_vert.second], adj_vert.second));
            }
        }
    }
}

vector<int> UGraphAL::get_path(int from, int to)
{
    dijkstra_algorithm(from);

    vector<int> path;
    path.push_back(from);

    get_path(path, to);

    return path;
}

void UGraphAL::get_path(vector<int>& path, int index)
{
    if (m_Path[index] == -1)
        return;

    get_path(path, m_Path[index]);

    path.push_back(index);
}