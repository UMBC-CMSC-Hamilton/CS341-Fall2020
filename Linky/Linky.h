#pragma once

// what is the difference?  
/*
	In a class, elements are private by default, in a struct they're public
*/
struct Node
{
	// forget that you need types, because it's not python./
	Node(int new_value)
		: value(new_value), p_next(nullptr)
	{
	}

	Node* p_next;
	int value;
};

class Linky
{
	public:
		// what does linky need?
		Linky();
		// & means what? copy constructor, yes
		Linky(const Linky& other_linky);
		// just get the value at p = position
		Node * GetAtPosition(int position);
		// insert at position
		void InsertAtPosition(int value, int position);
		// Remove at position
		bool RemoveAtPosition(int position);
		// assignment operator
		Linky& operator = (const Linky& other_linky);
		//
		// destructor
		~Linky();
	private:
		Node* p_head;
};

