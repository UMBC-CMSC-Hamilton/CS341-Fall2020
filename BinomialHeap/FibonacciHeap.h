//
// Created by Inarchus on 11/6/2020.
//

#ifndef HEAPS_FIBONACCIHEAP_H
#define HEAPS_FIBONACCIHEAP_H

#include <vector>
using std::vector;

class EmptyFibonacciHeap: public std::exception
{};

struct FibonacciNode
{
    FibonacciNode(int new_value=0)
        : value(new_value), marked(false), parent(nullptr)
    {};

    ~FibonacciNode()
    {
        for (unsigned int i = 0; i < children.size(); i++)
        {
            delete children[i];
        }
    }

    int rank() const
    {
        return children.size();
    }

    int value;
    bool marked;
    vector<FibonacciNode *> children;
    FibonacciNode * parent;
};

class FibonacciHeap {
    public:
        FibonacciHeap();
        void insert(int element);
        FibonacciNode * find_node(int key) const;
        void decrease_key(FibonacciNode * node, int new_key);
        int get_min() const;
        int remove_min();
        void consolidate();
        void merge(FibonacciHeap & fib);
        bool empty() const;
        void display() const;
    private:
        void display_rec(FibonacciNode * current, int tab_level = 0) const;
        FibonacciNode * find_node_rec(int key, FibonacciNode * current) const;

        vector<FibonacciNode *> root_list;
        FibonacciNode * min_pointer;
};


#endif //HEAPS_FIBONACCIHEAP_H
