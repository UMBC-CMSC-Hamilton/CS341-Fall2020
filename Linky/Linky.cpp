#include "Linky.h"

// this will create an empty linked list, which is what we want.
Linky::Linky()
	: p_head(nullptr)
{
	// not complex
}
// & means what? copy constructor
Linky::Linky(const Linky& other_linky)
{
	// you just sit here.  now we're ready...
	if (other_linky.p_head)
	{
		p_head = new Node(other_linky.p_head->value);
		// this is ok because we know that other_linky.p_head exists
		Node* p_read = other_linky.p_head->p_next;
		// our new linked list's head.  
		Node* p_write = p_head;
		while (p_read)
		{
			// make new node and copy value
			p_write->p_next = new Node(p_read->value);
			// advance
			// old linked list
			p_read = p_read->p_next;
			// the new linked list
			p_write = p_write->p_next;
		}
		// done, :)
	}
	else
	{
		// wow
		p_head = nullptr;
	}
}

// get at position
Node * Linky::GetAtPosition(int position)
{
	Node* p_current = p_head;
	for (int i = 0; i < position; i++)
	{
		if (p_current != nullptr) // if (p_current)
		{
			// i can't just do this.   
			p_current = p_current->p_next;
			// maybe p_current was null so if it is this is a segfault.  
		}
		else
		{
			// throw some not found exception
			return nullptr;
		}
	}

	// a little bit unsafe, because it gives access to the internal structure to the outside coder.  
	// cool we're going to do it anyway
	return p_current;
}



// insert at position
void Linky::InsertAtPosition(int value, int position)
{
	// either you're inserting at the head, or you're not = shocking
	if (position == 0)
	{
		// new node pointer
		Node* p_new = new Node(value);
		// assign the old head to be the next node in the chain.
		p_new->p_next = p_head;
		// might forget that p_head existed before... now we haven't.  
		p_head = p_new;
		// instead of doing else
		return;
	}
	if (!p_head)
	{
		// throw an exception, return false, didn't insert
		// fail silently
		return;
	}

	Node* p_current = p_head->p_next;
	Node* p_previous = p_head;
	
	int i = 1;
	while (i < position && p_current != nullptr)
	{
		i++;
		// advances previous to current
		p_previous = p_current;
		// advances current to next
		p_current = p_current->p_next;
	}

	// maybe the linked list isn't long enough
	if (i < position)
	{
		return;
	}
	else
	{
		// finally insert p_previous->p_next used to be p_current
		p_previous->p_next = new Node(value);
		// now we have to relink by setting 
		p_previous->p_next->p_next = p_current;
	}
}
// Remove at position
bool Linky::RemoveAtPosition(int position)
{
	if (!p_head)
	{
		// linked list is empty, no elements removed
		return false;
	}
	if (position == 0) // and we haven't returned so we know that the head has a node.
	{
		// it forgets p_head (never deletes it)
		Node* p_old_head = p_head;
		// we're done right?
		p_head = p_head->p_next;
		// we still have to remember to delete the old head.
		delete p_old_head;
		return true;
	}
	else
	{
		// safe is because if p_head is null then we've already booted out of this function
		Node* p_previous = p_head;
		// this line could cause a seg fault
		Node* p_current = p_head->p_next;
		for (int i = 0; i < position; i++)
		{
			if (p_current != nullptr) // if (p_current)
			{
				p_previous = p_current;
				p_current = p_current->p_next;
			}
			else
			{
				// throw some not found exception
				return false;
			}
		}
		// position now correct
		if (!p_current)
		{
			// why did i have to check this one more time?
			return false;
		}
		else
		{
			// p_previous and p_current are not null, we don't know p-current->p_next isn't, but it's ok
			p_previous->p_next = p_current->p_next;
			// kill off the node
			delete p_current;
			// because the function does that when it works
			return true;
		}
	}
}
// assignment operator
Linky& Linky::operator = (const Linky& other_linky)
{
	// can't forget what happens if current linked list already exists... 
	if (p_head)
	{
		Node* p_current = p_head->p_next;
		Node* p_del_node = p_head;

		// non tricky
		while (p_current)
		{
			p_del_node = p_current;
			p_current = p_current->p_next;
			delete p_del_node;
		}
		delete p_head;
	}

	// you just sit here.  now we're ready...
	if (other_linky.p_head)
	{
		p_head = new Node(other_linky.p_head->value);
		// this is ok because we know that other_linky.p_head exists
		Node* p_read = other_linky.p_head->p_next;
		// our new linked list's head.  
		Node* p_write = p_head;
		while (p_read)
		{
			// make new node and copy value
			p_write->p_next = new Node(p_read->value);
			// advance
			// old linked list
			p_read = p_read->p_next;
			// the new linked list
			p_write = p_write->p_next;
		}
		// done, :)
	}
	else
	{
		// wow
		p_head = nullptr;
	}
	// this is a pointer in C++ to the current class... so in order to return it we have to dereference it.  
	return *this;
}

// destructor
Linky::~Linky()
{
	// if the linked list exists
	if (p_head)
	{
		Node* p_current = p_head->p_next;
		Node* p_del_node = p_head;

		// non tricky
		while (p_current)
		{
			p_del_node = p_current;
			p_current = p_current->p_next;
			delete p_del_node;
		}
		// just deallocate the head, doesn't zero the pointer.
		delete p_head;
	}
	// theoretically possible that if the class is destroyed but not really, it can be used again
	p_head = nullptr;
}