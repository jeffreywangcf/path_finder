#pragma once
#include<iostream>
#include<cassert>
template<typename Weight>
class Edge
{
private:
    int node1;
    int node2;
    Weight m_weight;
public:
    Edge(){}
    Edge(int a, int b, Weight weight): node1(a), node2(b)
    {
        m_weight = weight;
    }
    ~Edge() = default;
    int first(){return node1;}
    int second(){return node2;}
    Weight GetWeight(){return m_weight;}
    int GetOther(int current)
    {
        assert(current == node1 || current == node2);
        return current == node1 ? node2 : node1;
    }
    friend std::ostream &operator<<(std::ostream & output, Edge<Weight> & that)
    {
        output << that.first() << " - " << that.second() << ": " << that.GetWeight();
        return output;
    }
    bool operator<(Edge<Weight> & that){return this->GetWeight() < that.GetWeight();}
    bool operator<=(Edge<Weight> & that){return this->GetWeight() <= that.GetWeight();}
    bool operator>(Edge<Weight> & that){return this->GetWeight() > that.GetWeight();}
    bool operator>=(Edge<Weight> & that){return this->GetWeight() >= that.GetWeight();}
    bool operator==(Edge<Weight> & that){return this->GetWeight() == that.GetWeight();}
    bool operator!=(Edge<Weight> & that){return this->GetWeight() != that.GetWeight();}
};