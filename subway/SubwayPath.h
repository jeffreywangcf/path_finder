#include "graph_algo/Edge.h"
#include "graph_algo/IndexMinHeap.h"
#include<vector>
#include<fstream>
#include<iostream>
#include<sstream>

using namespace std;

template<typename Graph, typename Weight>
class LoadPaths
{
public:
    LoadPaths(Graph & graph, const string & filename, vector<vector<int>> &table)
    {
        assert(table.size() == graph.GetPoint());
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
            int subwayLine;
            stringstream ss(line);
            ss >> point1 >> point2 >> subwayLine >> weight;
            graph.AddEdge(point1, point2, weight);
            table[point1][point2] = subwayLine;
            table[point2][point1] = subwayLine;
        }
        file.close();
    }
};