
#include "BinomialHeap.h"
#include <iostream>
using namespace std;

BinomialHeap::BinomialHeap()
{
    p_root = new BinomialHeapNode(-1);
}

BinomialHeap::~BinomialHeap()
{
    delete p_root;
    p_root = nullptr;
}

void BinomialHeap::insert(int new_value)
{
    // insert is merge
    auto * fictional_root = new BinomialHeapNode(-1);
    auto * new_bin_heap = new BinomialHeapNode(new_value);
    fictional_root->insert_as(new_bin_heap, 0);
    merge(p_root, fictional_root);
    delete fictional_root;
}
int BinomialHeap::get_min() const
{
    int current_min = INT32_MAX;
    for(int i = 0; i < p_root->children.size(); i++)
    {
        if(p_root->children[i])
        {
            if(p_root->children[i]->value < current_min)
            {
                current_min = p_root->children[i]->value;
            }
        }
    }
    return current_min;
}
int BinomialHeap::remove_min()
{
    int current_min = INT32_MAX;
    int min_index = -1;
    for(int i = 0; i < p_root->children.size(); i++)
    {
        if(p_root->children[i])
        {
            if(p_root->children[i]->value < current_min)
            {
                current_min = p_root->children[i]->value;
                min_index = i;
            }
        }
    }

    if(min_index != -1)
    {
        auto * delete_node = p_root->children[min_index];
        // dont' forget to forget
        // more applicable to your project in setPriorityFn (you will need to remember to forget)
        p_root->children[min_index] = nullptr;
        // this was the bug
        merge(p_root, delete_node);
        // clear the children so that i don't delete them
        delete_node->children.clear();
        // they got merged into the old heap, we don't them to die.
        delete delete_node;
    }

    return current_min;
}

void BinomialHeap::merge(BinomialHeap & other_heap)
{
    merge(p_root, other_heap.p_root);
    // clear out the other heap
    other_heap.p_root->children.clear();
}


/*
 * This thing is terrifying, i don't have a clue what the heck this does...
 */
void BinomialHeap::merge(BinomialHeapNode * p_heap, BinomialHeapNode * other_root)
{
    int max_children = 0;
    if(p_heap->children.size() > other_root->children.size())
    {
        max_children = p_heap->children.size();
    }
    else {
        max_children = other_root->children.size();
    }
    BinomialHeapNode * carry = nullptr;
    BinomialHeapNode * temp = nullptr;
    for (int current = 0; current < max_children; current++)
    {

        // if we have two B_{currents}
        if(p_heap->get_node(current) && other_root->get_node(current))
        {
            cout << "merging two B" << current << endl;
            // merge them p_heap is less then
            if(p_heap->get_node(current)->value <= other_root->get_node(current)->value)
            {
                // this is adding the other-root's B_current as a child to our B_current
                // makes a B_{current + 1}
                p_heap->get_node(current)->children.push_back(other_root->get_node(current));
                temp = p_heap->get_node(current);
            } else{
                other_root->get_node(current)->children.push_back(p_heap->get_node(current));
                temp = other_root->get_node(current);
            }
            p_heap->insert_as(nullptr, current);
            other_root->insert_as(nullptr, current);
            if(carry)
            {
                cout << current << "the carry value is " << carry->value << endl;
                // B_{current + 1}
                p_heap->insert_as(carry, current);
            }
            carry = temp;
        }
        else if(p_heap->get_node(current) && carry)
        {
            if(p_heap->get_node(current)->value <= carry->value)
            {
                p_heap->get_node(current)->children.push_back(carry);
                // setting merged thing as a B(current + 1)
                carry = p_heap->get_node(current);
                // nulling out whatever was at position current
            } else {
                carry->children.push_back(p_heap->get_node(current));
            }
            p_heap->insert_as(nullptr, current);
        }
        else if(other_root->get_node(current) && carry)
        {
            if(other_root->get_node(current)->value <= carry->value)
            {
                other_root->get_node(current)->children.push_back(carry);
                // setting merged thing as a B(current + 1)
                carry = other_root->get_node(current);
                // nulling out whatever was at position current
            } else {
                carry->children.push_back(other_root->get_node(current));
            }
            p_heap->insert_as(nullptr, current);
        }
        else
        {
            // one or zero B_i exists
            // copy it into our heap
            if(other_root->get_node(current))
            {
                p_heap->insert_as(other_root->get_node(current), current);
            }
            else if (carry)
            {
                cout << "carrying" << endl;
                p_heap->insert_as(carry, current);
            }
            carry = nullptr;
        }
    }
    // at the very end, what if we have a carry left over.... !!!!!
    if(carry)
    {
        p_heap->children.push_back(carry);
    }
    // the other root needs to forget about its children
    other_root->children.clear();
}


void BinomialHeap::display()
{
    display(p_root, 0);
}


void BinomialHeap::display(BinomialHeapNode * p_node, int tab_level)
{
    for(int k = 0; k < p_node->children.size(); k++)
    {
        if(p_node->children[k])
        {
            for(int i = 0; i < tab_level; i++)
                cout << "\t";
            cout << "B" << k << ": " << p_node->children[k]->value << endl;
            display(p_node->children[k], tab_level + 1);
        } else
        {
            cout << "B" << k << ": None" << endl;
        }
    }
}