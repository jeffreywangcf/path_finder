#pragma once
#include<iostream>
#include<vector>
#include<cassert>
#include"Edge.h"
#include"IndexMinHeap.h"
#include"UnionFind.h"

template<typename Graph, typename Weight>
class Prim
{
private:
    Graph &m_graph;
    IndexMinHeap<Weight> m_priorityQueue;
    vector<Edge<Weight> *> __edgeTo__;
    bool *ifVisited;
    vector<Edge<Weight>> m_minSpanTree;
    Weight treeWeight;
    void visit(int target);

public:
    Prim() = delete;
    explicit Prim(Graph &graph);
    ~Prim(){delete[] ifVisited;}
    function<vector<Edge<Weight>>()> getEdges = [&](){return m_minSpanTree;};
    Weight GetWeight() {return treeWeight;}
};
template<typename Graph, typename Weight>
void Prim<Graph, Weight>::visit(int target)
{
    assert(!ifVisited[target]);
    ifVisited[target] = true;
    typename Graph::AdjacentIterator adj(m_graph, target);
    for(Edge<Weight>* node = adj.begin(); !adj.end(); node = adj.next())
    {
        int other = node->GetOther(target);
        if(!ifVisited[other])
        {
            if (!__edgeTo__[other])
            {
                __edgeTo__[other] = node;
                m_priorityQueue.insert(other, node->GetWeight());
            } else if (node->GetWeight() < __edgeTo__[other]->GetWeight())
            {
                __edgeTo__[other] = node;
                m_priorityQueue.change(other, node->GetWeight());
            }
        }
    }
}
template<typename Graph, typename Weight>
Prim<Graph, Weight>::Prim(Graph &graph): m_graph(graph), m_priorityQueue(IndexMinHeap<Weight>(graph.GetPoint()))
{
    treeWeight = Weight();
    assert(graph.GetEdge() >= 1);
    ifVisited = new bool[graph.GetPoint()];
    for(int i = 0; i < graph.GetPoint(); i++)
    {
        ifVisited[i] = false;
        __edgeTo__.push_back(nullptr);
    }
    m_minSpanTree.clear();
    visit(0);
    while(!m_priorityQueue.isEmpty())
    {
        int minIndex = m_priorityQueue.extractMinIndex();
        assert(__edgeTo__[minIndex]);
        m_minSpanTree.push_back(*__edgeTo__[minIndex]);
        visit(minIndex);
    }
    for(auto &a : m_minSpanTree)
        treeWeight += a.GetWeight();
}

template<typename Graph, typename Weight>
class Kruskal
{
private:
    Graph &m_graph;
    vector<Edge<Weight>> m_MinSpanTree;
    Weight treeWeight;
public:
    Kruskal() = delete;
    explicit Kruskal(Graph &graph);
    function<vector<Edge<Weight>>()> getEdges = [&](){return m_MinSpanTree;};
    Weight GetWeight() {return treeWeight;}
};
template<typename Graph, typename Weight>
Kruskal<Graph, Weight>::Kruskal(Graph &graph): m_graph(graph), treeWeight(Weight())
{
    MinHeap<Edge<Weight>> edgePQ = MinHeap<Edge<Weight>>(m_graph.GetEdge());
    for(int i = 0; i < m_graph.GetPoint(); i++)
    {
        typename Graph::AdjacentIterator adj(m_graph, i);
        for(Edge<Weight> *node = adj.begin(); !adj.end(); node = adj.next())
            if(node->first() < node->second())
                edgePQ.insert(*node);
    }
    UnionFind table = UnionFind(m_graph.GetEdge());
    while(!edgePQ.isEmpty() && m_MinSpanTree.size() < m_graph.GetEdge() - 1)
    {
        Edge<Weight> current = edgePQ.extractMin();
        if(table.isConnected(current.first(), current.second()))
            continue;
        m_MinSpanTree.push_back(current);
        table.unionElements(current.first(), current.second());
    }
    for(auto &a : m_MinSpanTree)
        treeWeight += a.GetWeight();
}