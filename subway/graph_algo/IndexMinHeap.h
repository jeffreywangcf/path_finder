#pragma once
#include<iostream>
#include<cassert>
#include<algorithm>
using namespace std;
template<typename Item = int>
class IndexMinHeap
{
private:
    Item *mi_data;
    int *mi_index;
    int *mi_reverse;
    int const mi_capacity;
    int mi_count;
    void __shiftUp__(int target_index);
    void __shiftDown__(int target_index);
public:
    function<bool(int)> __contain__ = [&](int target_index) ->
            bool{return mi_reverse[target_index + 1] != 0;};
    IndexMinHeap() = delete;
    ~IndexMinHeap();
    explicit IndexMinHeap(int capacity);
    function<bool()> isEmpty = [&]()->bool {return mi_count == 0;};
    function<int()> getSize = [&]()->int {return mi_count;};
    void insert(int i, Item NewItem);
    Item extractMin();
    int extractMinIndex();
    Item getMin();
    int getMinIndex();
    void change(int index, int NewItem);
    
};
template<typename Item>
IndexMinHeap<Item>::IndexMinHeap(int capacity): mi_capacity(capacity), mi_count(0)
{
    mi_data = new Item[mi_capacity + 1];
    mi_index = new int[mi_capacity + 1];
    mi_reverse = new int [mi_capacity + 1];
    for(int i = 0; i < mi_capacity; i++)
        mi_reverse[i] = int();
}
template<typename Item>
IndexMinHeap<Item>::~IndexMinHeap()
{
    delete[] mi_data;
    delete[] mi_index;
    delete[] mi_reverse;
}
template<typename Item>
void IndexMinHeap<Item>::__shiftUp__(int target_index)
{
    while(target_index > 1 && mi_data[mi_index[target_index]] < mi_data[mi_index[target_index / 2]])
    {
        swap(mi_index[target_index], mi_index[target_index / 2]);
        mi_reverse[mi_index[target_index]] = target_index;
        mi_reverse[mi_index[target_index / 2]] = target_index / 2;
        target_index /= 2;
    }
}
template<typename Item>
void IndexMinHeap<Item>::__shiftDown__(int target_index)
{
    while(target_index * 2 <= mi_count)
    {
        int next = target_index * 2;
        if(next + 1 <= mi_count && mi_data[mi_index[next + 1]] < mi_data[mi_index[next]])
            next++;
        if(mi_data[mi_index[target_index]] <= mi_data[mi_index[next]])
            break;
        swap(mi_index[target_index], mi_index[next]);
        mi_reverse[mi_index[next]] = next;
        mi_reverse[mi_index[target_index]] = target_index;
        target_index = next;
    }
}
template<typename Item>
void IndexMinHeap<Item>::insert(int i, Item NewItem)
{
    assert(mi_count + 1 <= mi_capacity);
    assert(i + 1 >= 1 && i + 1 <= mi_capacity);
    i++;
    mi_data[i] = NewItem;
    mi_index[mi_count + 1] = i;
    mi_reverse[i] = mi_count + 1;
    mi_count++;
    __shiftUp__(mi_count);
}
template<typename Item>
Item IndexMinHeap<Item>::extractMin()
{
    assert(mi_count > 0);
    Item ret = mi_data[mi_index[1]];
    swap(mi_index[1], mi_index[mi_count]);
    mi_reverse[mi_index[mi_count]] = 0;
    mi_reverse[mi_index[1]] = 1;
    mi_count--;
    __shiftDown__(1);
    return ret;
}
template<typename Item>
Item IndexMinHeap<Item>::getMin()
{
    assert(mi_count > 0);
    return mi_data[mi_index[1]];
}
template<typename Item>
int IndexMinHeap<Item>::extractMinIndex()
{
    assert(mi_count > 0);
    int ret = mi_index[1] - 1;
    swap(mi_index[1], mi_index[mi_count]);
    mi_reverse[mi_index[1]] = 1;
    mi_reverse[mi_index[mi_count]] = 0;
    mi_count--;
    __shiftDown__(1);
    return ret;
}
template<typename Item>
int IndexMinHeap<Item>::getMinIndex()
{
    assert(mi_count > 0);
    return mi_index[1] - 1;
}
template<typename Item>
void IndexMinHeap<Item>::change(int index, int NewItem)
{
    assert(__contain__(index));
    index++;
    mi_data[index] = NewItem;
    __shiftUp__(mi_reverse[index]);
    __shiftDown__(mi_reverse[index]);
}

template<typename Item>
class MinHeap
{
private:
    Item *m_data;
    int mi_count;
    int mi_capacity;
    void __shiftUp__(int k)
    {
        while(k > 1 && m_data[k/2] > m_data[k])
        {
            swap(m_data[k/2], m_data[k]);
            k = k/2;
        }
    }
    void __shiftDown__(int k)
    {
        while(2 * k <= mi_count)
        {
            int j = 2 * k;
            if(j + 1 <= mi_count && m_data[j + 1] < m_data[j])
                j++;
            if(m_data[k] <= m_data[j])
                break;
            swap(m_data[k], m_data[j]);
            k = j;
        }
    }
public:
    explicit MinHeap(int capacity): mi_capacity(capacity)
    {
        m_data = new Item[mi_capacity + 1];
        mi_count = 0;
    }
    MinHeap(Item arr[], int n): mi_capacity(n)
    {
        m_data = new Item[n + 1];
        for(int i = 0; i < n; i++)
            m_data[i+1] = arr[i];
        mi_count = n;
    }
    ~MinHeap(){delete[] m_data;}
    function<int()> size = [&]()->int{return mi_count;};
    function<bool()> isEmpty = [&]()->bool{return mi_count == 0;};
    void insert(Item item)
    {
        assert(mi_count + 1 <= mi_capacity);
        m_data[mi_count + 1] = item;
        __shiftUp__(mi_count + 1);
        mi_count++;
    }
    Item extractMin()
    {
        assert(mi_count > 0);
        Item ret = m_data[1];
        swap(m_data[1], m_data[mi_count]);
        mi_count--;
        __shiftDown__(1);
        return ret;
    }
    Item getMin()
    {
        assert(mi_count > 0);
        return m_data[1];
    }
};