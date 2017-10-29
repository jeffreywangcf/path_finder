#include "../graph_algo/IndexMinHeap.h"
#include "../graph_algo/ReadGraph.h"
#include "../graph_algo/Graph.h"
#include "../graph_algo/ShortestPath.h"

int test_main()
{
    string filename = "/Users/Excited/CLionProjects/graph_algorithms/data/long.txt";
    Graph<int> graph = Graph<int>(67);
    ReadGraph<Graph<int>, int> prim = ReadGraph<Graph<int>, int>(graph, filename);


//    Prim<Graph<double>, double> sp = Prim<Graph<double>, double>(graph);
//    auto path1 = sp.getEdges();
//    for (auto &a : path1)
//        cout<< a <<endl;
//    cout << "total: " << sp.GetWeight() << endl;
//
//    cout << endl;
//
//    Kruskal<Graph<double>, double> kruskal = Kruskal<Graph<double>, double>(graph);
//    auto path2 = kruskal.getEdges();
//    for(auto &a : path2)
//        cout << a << endl;
//    cout << "total: " << kruskal.GetWeight() << endl;
//
//    cout<<endl;
//
    Dijkstra<Graph<int>, int> dij = Dijkstra<Graph<int>, int>(graph, 9);
    dij.showPath(25);
}