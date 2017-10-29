cmake_minimum_required(VERSION 3.8)
project(subway)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp graph_algo/Edge.h graph_algo/Graph.h graph_algo/IndexMinHeap.h graph_algo/MinSpanTree.h graph_algo/ReadGraph.h graph_algo/ShortestPath.h graph_algo/UnionFind.h test/test_main.cpp)
add_executable(subway ${SOURCE_FILES})