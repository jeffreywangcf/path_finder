#pragma once
#include<iostream>
#include<cassert>
using namespace std;

class UnionFind
{
private:
    int *mi_rank;
    int *mi_parent;
    int mi_count;
public:
    UnionFind() = delete;
    explicit UnionFind(int count): mi_count(count)
    {
        mi_rank = new int[mi_count];
        mi_parent = new int[mi_count];
        for(int i = 0; i < mi_count; i++)
        {
            mi_rank[i] = 1;
            mi_parent[i] = i;
        }
    }
    ~UnionFind()
    {
        delete[] mi_parent;
        delete[] mi_rank;
    }
    int find(int p)
    {
        assert(p >= 0 && p < mi_count);
        while(p != mi_parent[p])
        {
            mi_parent[p] = mi_parent[mi_parent[p]];
            p = mi_parent[p];
        }
        return p;
    }
    function<bool(int, int)> isConnected = [&](int p, int q) -> bool{return find(p) == find(q);};
    void unionElements(int p, int q)
    {
        int pRoot = find(p);
        int qRoot = find(q);
        if(pRoot == qRoot)
            return;
        if(mi_rank[pRoot] < mi_rank[qRoot])
            mi_parent[pRoot] = qRoot;
        else if(mi_rank[pRoot] > mi_rank[qRoot])
            mi_parent[qRoot] = pRoot;
        else
        {
            mi_parent[pRoot] = qRoot;
            mi_rank[qRoot]++;
        }
    }
};