#include "graph_algo/IndexMinHeap.h"
#include "graph_algo/ReadGraph.h"
#include "graph_algo/Graph.h"
#include "graph_algo/ShortestPath.h"
#include "SubwayPath.h"
#include<unordered_map>
#include<cassert>
#include<cstdio>

#define NODE_LOC "/Users/Excited/CLionProjects/subway/data/nodes.txt"
#define DICT_LOC "/Users/Excited/CLionProjects/subway/data/dict.txt"

#define START_NAME "Oakland Park"
#define END_NAME "Yeiv Garden"

int main()
{
    
    
    Graph<int> graph = Graph<int>(67);
    auto lineTable = std::vector<std::vector<int>>(graph.GetPoint(), vector<int>(graph.GetPoint(), -1));
    auto read = LoadPaths<Graph<int>, int>(graph, NODE_LOC, lineTable);
    
    unordered_map<int, string> numToName;
    unordered_map<string, int> nameToNum;
    ifstream file(DICT_LOC);
    assert(file.is_open());
    string source;
    int len;
    getline(file, source);
    stringstream ss1(source);
    ss1 >> len;
    for(int i = 0; i < len; i++)
    {
        string num, station;
        getline(file, source);
        stringstream ss(source);
        ss >> num;
        station = source.substr(num.length() + 1).data();
        numToName[stoi(num)] = station;
        nameToNum[station] = stoi(num);
    }
    
    int S_START = nameToNum[START_NAME];
    int S_END = nameToNum[END_NAME];
    
    Dijkstra<Graph<int>, int> dij = Dijkstra<Graph<int>, int>(graph, S_START);
    vector<Edge<int>> path;
    dij.getShortestPath(S_END, path);
    
    
    printf("route: %s  -----  %s\n\n", numToName[S_START].c_str(), numToName[S_END].c_str());
    int count = 1;
    int distance, totalStops = int();
    auto first = path[0];
    distance += first.GetWeight();
    totalStops++;
    int currentLine = lineTable[first.first()][first.second()];
    printf("you are now at station %s on line %d, %s direction.\n", numToName[first.first()].c_str(), currentLine, numToName[first.second()].c_str());
    for(int i = 1; i < path.size(); i++)
    {
        auto current = path[i];
        if(lineTable[current.first()][current.second()] != currentLine)
        {
            currentLine = lineTable[current.first()][current.second()];
            printf("After %d stops, at station %s transfer to line %d, %s direction.\n",
                   count, numToName[current.first()].c_str(), currentLine, numToName[current.second()].c_str());
            count = 1;
        }
        else
            count++;
        distance += current.GetWeight();
        totalStops++;
    }
    printf("after %d stops, you arrive at your destination %s.\n", count, numToName[S_END].c_str());
    printf("total distance: %d\ttotal stops: %d\n", distance, totalStops);
}
