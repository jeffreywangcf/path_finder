#pragma once

#include <fstream>
#include <ctime>
#include <string>
#include <cassert>
#include <sstream>
using namespace std;
template<typename Graph, typename Weight>
class ReadGraph
{
public:
    ReadGraph(Graph & graph, const string & filename)
    {
        ifstream file(filename);
        string line;
        int node1, node2;
        assert(file.is_open());
        assert(getline(file, line));
        stringstream ss(line);
        ss >> node1 >> node2;
        assert(node1 == graph.GetPoint());
        for(int i = 0; i < node2; i++)
        {
            getline(file, line);
            int point1, point2;
            Weight weight;
            stringstream ss(line);
            ss >> point1 >> point2 >> weight;
            graph.AddEdge(point1, point2, weight);
        }
        file.close();
    }
};