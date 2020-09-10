#pragma once

#include<vector>
using namespace std;

/*
	This code should sort a list....
*/
void stupidBubbleSort(vector<int>& list_to_sort)
{
	int temp;
	// what does bubble sort do?
	for (int i = 0; i < list_to_sort.size(); i++) // this for loop runs N times...
	{
		// i'll explain why i did the - 1 in just a second
		for (int j = 0; j < list_to_sort.size() - 1; j++) // this for loop runs N - 1 times
		{
			// if they're not in the correct order, flip them:
			// compares elements with elements next to it
			if (list_to_sort[j] > list_to_sort[j + 1]) // if statment so maybe 1 operation? or maybe... 3 or something I don't know
			{
				temp = list_to_sort[j]; // constant time
				list_to_sort[j] = list_to_sort[j + 1]; // constant time
				list_to_sort[j + 1] = temp; // constant time
			} // 4 steps, because it's 4 lines.  
		}
	}
}

void improvedBubbleSort(vector<int>& list_to_sort)
{
	int temp;
	// what does bubble sort do?
	bool swapped = true;
	int i = 0; 
	while (swapped)
	{
		swapped = false;
		// i'll explain why i did the - 1 in just a second
		for (int j = 0; j < list_to_sort.size() - 1 - i; j++) // this for loop runs N - 1 times
		{
			// if they're not in the correct order, flip them:
			// compares elements with elements next to it
			if (list_to_sort[j] > list_to_sort[j + 1]) // if statment so maybe 1 operation? or maybe... 3 or something I don't know
			{
				swapped = true;
				temp = list_to_sort[j]; // constant time
				list_to_sort[j] = list_to_sort[j + 1]; // constant time
				list_to_sort[j + 1] = temp; // constant time
			} // 4 steps, because it's 4 lines.  
		}
		i++;
		// in terms of code, this is pretty mangled now, we would probably want to rewrite this a bit, not gonna!
	}
}

void selectionSort(vector<int>& list_to_sort)
{
	int min_index = 0;
	int temp;
	// sorts the list
	// N steps...
	for (int i = 0; i < list_to_sort.size(); i++)
	{
		// j = i because the list is already sorted up to i...
		// finds the min
		min_index = i;
		for (int j = i; j < list_to_sort.size(); j++) 
			// doesn't start at 0, it starts at i, N - i steps per go
		{
			if (list_to_sort[j] < list_to_sort[min_index])
			{
				min_index = j;
			}
			if (min_index != i)
			{
				// you might write a swap function, just have to remember swap is O(1).  
				// alg is constant time, O(1) our_alg < C * 1, for a C we get to pick.  
				// the point is O(1) = O(4)
				temp = list_to_sort[min_index]; // constant time
				list_to_sort[min_index] = list_to_sort[i]; // constant time
				list_to_sort[i] = temp; // constant time
			} // 6 steps or so?
		}
	}
}

// just merge takes two sorted!!!!!! sublists 
// garbage in garbage out if they're not sorted...
// give us back a sorted sublist made of both of them.  
vector<int>& merge(vector<int>& v1, vector<int>& v2)
{
	vector<int> result;
	
	int index_1 = 0, index_2 = 0;
	while (index_1 < v1.size() && index_2 < v2.size())
	{
		if (v1[index_1] <= v2[index_2])
		{
			result.push_back(v1[index_1]);
			index_1++;
		}
		else 
		{
			result.push_back(v2[index_2]);
			index_2++;
		}
	}
	// 2 5 7 9 ->; 1 3 8 10 ->
	// 1, 2, 3, 5, 7, 8, 9, 10
	// now it is done

	// 2 2 2 2 ->; 5 5 5 5 ->
	// 2, 2, 2, 2, 5, 5, 5, 5
	// now it is sorted

	while (index_1 < v1.size())
	{
		result.push_back(v1[index_1]);
		index_1++;
	}
	while (index_2 < v2.size())
	{
		result.push_back(v2[index_2]);
		index_2++;
	}
	return result;
}

vector<int>& merge_sort(vector<int> & list_to_sort)
{
	if (list_to_sort.size() > 1)
	{
		vector<int> front_list;
		for (int i = 0; i < list_to_sort.size() / 2; i++)
		{
			front_list.push_back(list_to_sort[i]);
		}
		vector<int> back_list;
		for (int j = list_to_sort.size() / 2; j < list_to_sort.size(); j++)
		{
			back_list.push_back(list_to_sort[j]);
		}
		// not the most stupid thing, still pretty dumb - inefficient to have to copy these over and over
		merge_sort(front_list);
		// get to assume that the front part is sorted... 
		merge_sort(back_list);
		// now we can assume that the back part of the list is sorted.  
		return merge(front_list, back_list);
	}
	return list_to_sort;
}

/*
	Best Case: O(n lg(n))
	Worst Case: O(n^2) - quadratic sort
	Expected Case: O(n lg(n)) except in really bad cases, reversed list, sorted list.  
*/
// quick sort
vector<int>& quick_sort(vector<int>& list_to_sort)
{
	if (list_to_sort.size() > 1)
	{
		vector<int> less_list;
		vector<int> equal_list;
		vector<int> greater_list;
		// use a find-median alg runs in O(N) time
		// prevent the worst case from happening
		int pivot = list_to_sort[0];
		// definitely O(N)
		for (int i = 0; i < list_to_sort.size(); i++)
		{
			if (list_to_sort[i] < pivot)
			{
				less_list.push_back(list_to_sort[i]);
			}
			else if (list_to_sort[i] == pivot)
			{	// sort of an optimization
				equal_list.push_back(list_to_sort[i]);
			}
			else // trichotomy, x,y x < y x==y x > y
			{
				greater_list.push_back(list_to_sort[i]);
			}
		}
		// wait we never sorted the sublists
		less_list = quick_sort(less_list);
		greater_list = quick_sort(greater_list);

		vector<int> total_list;
		for (int x : less_list)
		{
			total_list.push_back(x);
		}
		for (int y : equal_list)
		{
			total_list.push_back(y);
		}
		for (int z : greater_list)
		{
			total_list.push_back(z);
		}
		
		return total_list;
	}
	else
	{
		return list_to_sort;
	}
}


// bucket sort O(n + n^2/ k + k) where k is the number of buckets

// insertion sort, how does that work?

void insertion_sort(vector<int>& list_to_sort)
{
	int j;
	int element;
	// i = the element we pull back as far as we need.  
	// just look at a single element in a list, can't pull it back
	for (int i = 1; i < list_to_sort.size(); i++)
	// always going to run N - 1  times, I'm just going to say N.   
	{
		j = i;
		// while we need to pull the element back a position
		element = list_to_sort[i];
		while (j > 0 && list_to_sort[j] < list_to_sort[j - 1])
			// this is going to run... anywhere between 0 times (just runs the check)
			// upto i times, where i goes from 1 to N.  
		{
			// swap elements forward
			list_to_sort[j] = list_to_sort[j - 1];
			// go back an element
			j--;
		}
		// wherever j ends up, could be 0, or it could be anything between 0 and i
		list_to_sort[j] = element;
	}
	// we're done.
}