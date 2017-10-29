#pragma once
#include<iostream>
#include<stack>
#include<vector>
#include "IndexMinHeap.h"
#include "Edge.h"
using namespace std;

template<typename Graph, typename Weight>
class Dijkstra
{
private:
    Graph &m_graph;
    int mi_start;
    Weight *m_distance;
    bool *m_ifVisited;
    vector<Edge<Weight> *> m_comefrom;
    std::function<bool(int)> hasPathTo = [&](int target)->bool{return m_ifVisited[target];};
public:
    Dijkstra() = delete;
    Dijkstra(Graph &graph, int s);
    ~Dijkstra()
    {
        delete[] m_distance;
        delete[] m_ifVisited;
        delete m_comefrom[0];
    }
    Weight getDistanceTo(int target)
    {
        assert(target >= 0 and target < m_graph.GetPoint( ));
        assert(hasPathTo(target));
        return m_distance[target];
    }
    void getShortestPath(int target, vector<Edge<Weight>> & vec);
    void showPath(int target);
};
template<typename Graph, typename Weight>
Dijkstra<Graph, Weight>::Dijkstra(Graph &graph, int s): m_graph(graph)
{
    assert(s >= 0 and s < m_graph.GetPoint());
    mi_start = s;
    m_distance = new Weight[m_graph.GetPoint()];
    m_ifVisited = new bool[m_graph.GetPoint()];
    for(int i = 0; i < m_graph.GetPoint(); i++)
    {
        m_distance[i] = Weight();
        m_ifVisited[i] = false;
        m_comefrom.push_back(nullptr);
    }
    IndexMinHeap<Weight> edgePQ(m_graph.GetPoint());
    m_distance[mi_start] = Weight();
    m_comefrom[mi_start] = new Edge<Weight>(mi_start, mi_start, Weight());
    edgePQ.insert(mi_start, m_distance[mi_start]);
    m_ifVisited[mi_start] = true;
    while(not edgePQ.isEmpty())
    {
        int minIndex = edgePQ.extractMinIndex();
        m_ifVisited[minIndex] = true;
        typename Graph::AdjacentIterator adj(m_graph, minIndex);
        for(Edge<Weight> *node = adj.begin(); not adj.end(); node = adj.next())
        {
            int other = node->GetOther(minIndex);
            if(not m_ifVisited[other])
            {
                if((m_comefrom[other] == nullptr) or (m_distance[minIndex] + node->GetWeight() < m_distance[other]))
                {
                    m_distance[other] = m_distance[minIndex] + node->GetWeight();
                    m_comefrom[other] = node;
                    if(edgePQ.__contain__(other))
                        edgePQ.change(other, m_distance[other]);
                    else edgePQ.insert(other, m_distance[other]);
                }
            }
        }
    }
}
template<typename Graph, typename Weight>
void Dijkstra<Graph, Weight>::getShortestPath(int target, vector<Edge<Weight>> &vec)
{
    assert(target >= 0 and target < m_graph.GetPoint());
    assert(hasPathTo(target));
    stack<Edge<Weight> *> storage;
    Edge<Weight> *current = m_comefrom[target];
    while(current->first() != this->mi_start)
    {
        storage.push(current);
        current = m_comefrom[current->first()];
    }
    storage.push(current);
    while(not storage.empty())
    {
        current = storage.top();
        vec.push_back(*current);
        storage.pop();
    }
}
template<typename Graph, typename Weight>
void Dijkstra<Graph, Weight>::showPath(int target)
{
    assert(target >= 0 and target < m_graph.GetPoint());
    assert(hasPathTo(target));
    vector<Edge<Weight>> vec;
    getShortestPath(target, vec);
    for(auto &a : vec)
        cout << a.first() << "->";
    cout << target << endl;
}