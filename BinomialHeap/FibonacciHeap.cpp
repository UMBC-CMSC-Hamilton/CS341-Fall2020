//
// Created by Inarchus on 11/6/2020.
//

#include <iostream>
using namespace std;

#include "FibonacciHeap.h"

FibonacciHeap::FibonacciHeap()
    : min_pointer(nullptr)
{

}
void FibonacciHeap::insert(int element)
{
    root_list.push_back(new FibonacciNode(element));
    if(!min_pointer)
    {
        min_pointer = root_list[0];
    }
    else if (min_pointer && min_pointer->value > element)
    {
        min_pointer = root_list[root_list.size() - 1];
    }

}

FibonacciNode * FibonacciHeap::find_node(int key) const
{
    FibonacciNode * p_candidate = nullptr;
    for(auto node: root_list)
    {
        p_candidate = find_node_rec(key, node);
        if(p_candidate)
            return p_candidate;
    }
    return nullptr;
}

FibonacciNode * FibonacciHeap::find_node_rec(int key, FibonacciNode * current) const
{
    FibonacciNode * p_candidate = nullptr;
    if(current)
    {
        if(current->value == key)
        {
            return current;
        }

        for (auto node: current->children)
        {
            p_candidate = find_node_rec(key, node);
            if(p_candidate)
                return p_candidate;
        }
    }
    return nullptr;
}

void FibonacciHeap::decrease_key(FibonacciNode * node, int new_key)
{
    if(node)
    {
        // case 1, no heap violation
        if((node->parent && new_key > node->parent->value) || !node->parent)
        {
            node->value = new_key;
        }
        else if(new_key < node->parent->value)
        {
            FibonacciNode * current = node;
            cout << "decreasing key from " << node->value << " to " << new_key << endl;
            current->value = new_key;

            while(current->parent && (current->value < current->parent->value || current->marked))
            {
                cout << "pushing " << current->value << " into root list " << current->parent->value << endl;
                root_list.push_back(current);
                current->marked = false;
                bool found = false;
                for(unsigned int j = 0; j < current->parent->children.size(); j++)
                {
                    if(current->parent->children[j] == current)
                    {
                        found = true;
                    }
                    else if (found)
                    {
                        current->parent->children[j - 1] = current->parent->children[j];
                    }
                }
                current->parent->children[current->parent->children.size() - 1] = nullptr;
                current->parent->children.pop_back();
                current = current->parent;
                root_list[root_list.size() - 1]->parent = nullptr;
            }
            if(current->parent)
                current->marked = true;
        }
    }
}

bool FibonacciHeap::empty() const
{
    return root_list.empty();
}

int FibonacciHeap::get_min() const
{
    if(min_pointer)
    {
        return min_pointer->value;
    }
    throw EmptyFibonacciHeap();
}

int FibonacciHeap::remove_min()
{
    if(empty())
    {
       throw EmptyFibonacciHeap();
    }
    int saved_value = min_pointer->value;
    // append all of the children to the root_list
    FibonacciNode * old_min_pointer = min_pointer;
    for(int i = 0; i < root_list.size(); i++)
    {
        if(root_list[i] == min_pointer)
        {
            for(int j = 0; j < min_pointer->children.size(); j++)
            {
                min_pointer->children[j]->parent = nullptr;
                root_list.push_back(min_pointer->children[j]);
                // remember to forget
                min_pointer->children[j] = nullptr;
            }
            root_list[i] = nullptr;
            break;
        }
    }

    consolidate();

    delete old_min_pointer;
    return saved_value;
}

void FibonacciHeap::consolidate()
{
    vector<FibonacciNode *> consolidation_list;
    FibonacciNode * current = nullptr;

    for (unsigned int i = 0; i < root_list.size(); i++)
    {
        if (root_list[i])
        {
            if(root_list[i]->rank() < consolidation_list.size())
            {
                if(!consolidation_list[root_list[i]->rank()])
                {
                    consolidation_list[root_list[i]->rank()] = root_list[i];
                }
                else
                {
                    current = root_list[i];
                    int j = current->rank();
                    while (j < consolidation_list.size() && current)
                    {
                        if(consolidation_list[j])
                        {
                            if(current->value < consolidation_list[j]->value)
                            {
                                current->children.push_back(consolidation_list[j]);
                                consolidation_list[j]->parent = current;
                            }
                            else
                            {
                                consolidation_list[j]->children.push_back(current);
                                current->parent = consolidation_list[j];
                                current = consolidation_list[j];
                            }
                            consolidation_list[j] = nullptr;
                        }
                        else
                        {
                            consolidation_list[j] = current;
                            current->parent = nullptr;
                            current = nullptr;
                        }
                        j++;
                    }
                    if(current)
                    {
                        consolidation_list.push_back(current);
                        current->parent = nullptr;
                        current = nullptr;
                    }
                }
            }
            else
            {
                while(consolidation_list.size() < root_list[i]->rank())
                {
                    consolidation_list.push_back(nullptr);
                }
                consolidation_list.push_back(root_list[i]);
            }
            // forget about it so it doesn't get destructed
            root_list[i] = nullptr;
        }
    }
    root_list = consolidation_list;
    // reassign min_pointer
    min_pointer = nullptr;
    for (auto node : root_list)
    {
        if(!min_pointer || (node && min_pointer->value > node->value))
        {
            min_pointer = node;
        }
    }
}

void FibonacciHeap::merge(FibonacciHeap & fib)
{
    for (auto node: fib.root_list)
    {
        if(node && !min_pointer)
        {

        }
        root_list.push_back(node);
    }
}

void FibonacciHeap::display() const
{
    for(FibonacciNode * node: root_list)
    {
        display_rec(node, 0);
    }
}

void FibonacciHeap::display_rec(FibonacciNode * current, int tab_level) const
{
    if(current)
    {
        for (int i = 0; i < tab_level; i++)
            cout << '\t' ;
        cout << "Rk" << current->children.size() << ": " << current->value;
        if (current->marked)
        {
            cout << " marked";
        }
        cout << endl;
        for(FibonacciNode * node: current->children)
        {
            display_rec(node, tab_level + 1);
        }
    }
}