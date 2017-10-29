#pragma once

#include <vector>
#include "Edge.h"
using namespace std;
template<typename Weight>
class Graph
{
private:
    int mi_point;
    int mi_edge;
    bool mb_isdirected;
    vector<vector<Edge<Weight> *>> mv_connection;
public:
    Graph() = delete;
    explicit Graph(int numpoint, bool direction = false): mi_point(numpoint), mb_isdirected(direction)
    {
        mi_edge = 0;
        for(int i = 0; i < mi_point; i++)
            mv_connection.push_back(vector<Edge<Weight> *>(mi_point, nullptr));
    }
    ~Graph()
    {
        for(int i = 0; i < mi_point; i++)
            for(int j = 0; j < mi_point; j++)
                if(mv_connection[i][j] != nullptr)
                    delete mv_connection[i][j];
    }
    int GetPoint(){return mi_point;}
    int GetEdge(){return mi_edge;}
    bool HasEdge(int i, int j)
    {
        assert(i >= 0 && i < mi_point);
        assert(j >= 0 && j < mi_point);
        return mv_connection[i][j] != nullptr;
    }
    void AddEdge(int node1, int node2, Weight weight)
    {
        assert(node1 >= 0 && node1 < mi_point);
        assert(node2 >= 0 && node2 < mi_point);
        if(HasEdge(node1, node2))
        {
            delete mv_connection[node1][node2];
            if(!mb_isdirected)
                delete mv_connection[node2][node1];
            mi_edge--;
        }
        mv_connection[node1][node2] = new Edge<Weight>(node1, node2, weight);
        if(!mb_isdirected)
            mv_connection[node2][node1] = new Edge<Weight>(node2, node1, weight);
        mi_edge++;
    }
    void show()
    {
        for(int i = 0; i < mi_point; i++)
        {
            cout << "vertex " << i << ": ";
            for(int j = 0; j < mi_point; j++)
            {
                if(mv_connection[i][j])
                    cout << *mv_connection[i][j] << "\t";
                else cout << "nullptr\t";
            }
            cout << endl;
        }
    }
    class AdjacentIterator
    {
    private:
        Graph & m_graph;
        int mi_element;
        int __index__;
    public:
        AdjacentIterator(Graph & graph, int element): m_graph(graph)
        {
            mi_element = element;
            __index__ = -1;
        }
        Edge<Weight>* begin()
        {
            __index__ = -1;
            return next();
        }
        Edge<Weight>* next()
        {
            for(__index__ += 1; __index__ < m_graph.GetPoint(); __index__++)
                if(m_graph.mv_connection[mi_element][__index__])
                    return m_graph.mv_connection[mi_element][__index__];
            return nullptr;
        }
        bool end()
        {
            return __index__ >= m_graph.GetPoint();
        }
    };
};