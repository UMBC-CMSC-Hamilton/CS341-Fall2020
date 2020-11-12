//
// Created by Inarchus on 10/27/2020.
//

#ifndef HEAPS_BINOMIALHEAP_H
#define HEAPS_BINOMIALHEAP_H
#include <vector>
using namespace std;

struct BinomialHeapNode {
    BinomialHeapNode(int new_value)
    : value(new_value)
    {}

    ~BinomialHeapNode()
    {
        for (unsigned int i = 0; i < children.size(); i++)
        {
            delete children[i];
        }
    }


    /*
     * Insert p_node as a B-i
     * B_7 into a node that only has had a B_2 before... we need to add a bunch of blank nullptr spaces
     */
    void insert_as(BinomialHeapNode * p_node, int i)
    {
        if (i >= children.size())
        {
            for(int j = children.size(); j < i; j++)
            {
                children.push_back(nullptr);
            }
            children.push_back(p_node);
        } else{
            children[i] = p_node;
        }
    }

    BinomialHeapNode * get_node(int i)
    {
        if(i < children.size())
        {
            return children[i];
        }
        return nullptr;
    }

    vector<BinomialHeapNode *> children;
    int value;
};

// exception that we throw
class BinomialHeapEmpty : public exception {};

class BinomialHeap {
    public:
        BinomialHeap();
        void insert(int new_value);
        int get_min() const;
        int remove_min();
        void merge(BinomialHeap & other_heap);
        bool empty() const;
        // code this up tonight or tomorrow
        void display();
        ~BinomialHeap();
    private:
        void merge(BinomialHeapNode * p_root, BinomialHeapNode * other_root);
        void display(BinomialHeapNode * p_node, int tab_level=0);
        // root won't have anything in it...
        BinomialHeapNode * p_root;
};


#endif //HEAPS_BINOMIALHEAP_H
