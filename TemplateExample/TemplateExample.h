#ifndef CS341_FALL20_HASHTABLES_TEMPLATEEXAMPLE_H
#define CS341_FALL20_HASHTABLES_TEMPLATEEXAMPLE_H

#include <exception>

class EmptyStack : public std::exception
{};

template<typename T>
struct StackNode
{
    explicit StackNode(T new_object)
        : p_next(nullptr), object(new_object)
    {}

    // in a struct everything is public
    StackNode * p_next;
    T object;
};


template<typename T>
class TemplateExample {
    public:
        TemplateExample();
        void eat(T new_t);
        T spit_out();

        ~TemplateExample();
        void clear();
        TemplateExample<T> & operator = (const TemplateExample<T> & other_te);
    private:
        StackNode<T> * p_top;
};

/*
 * IMPLEMENTATION OF TEMPLATE METHODS HERE
 */

template<typename T>
TemplateExample<T>::~TemplateExample()
{
    clear();
}

template<typename T>
void TemplateExample<T>::clear()
{
    StackNode<T> * old_top = nullptr;
    while(p_top)
    {
        old_top = p_top;
        p_top = p_top->p_next;
        delete old_top;
    }
    p_top = nullptr;
}


template<typename T>
TemplateExample<T>::TemplateExample()
    : p_top(nullptr)
{

}

template<typename T> // push
void TemplateExample<T>::eat(T new_t)
{
    StackNode<T> * p_new_top = new StackNode<T>(new_t);
    p_new_top->p_next = p_top;
    // i wasn't done, i can't implement a linked list
    p_top = p_new_top;
    // that's all we got to do here?? right??
}

template<typename T>
T TemplateExample<T>::spit_out() // pop
{
    if(p_top)
    {
        StackNode<T> * old_top = p_top;
        T remember_object = old_top->object;
        p_top = p_top->p_next;
        delete old_top;
        return remember_object;
    }
    throw EmptyStack();
    //"You tried to pop an empty stack, you are bad.  "
}

template<typename T>
TemplateExample<T> & TemplateExample<T>::operator = (const TemplateExample<T> & other_te)
{
    if(this != &other_te)
    {
        clear();
        if(other_te.p_top)
        {
            p_top = new StackNode<T>(other_te.p_top->object);
        }
        StackNode<T> * current = p_top;
        StackNode<T> * other_current = other_te.p_top;
        while(other_current->p_next)
        {
            // copy the next;
            current->p_next = new StackNode<T>(other_current->p_next->object);
            // advance
            current = current->p_next;
            other_current = other_current->p_next;
        }
    }

    return *this;
}

#endif //CS341_FALL20_HASHTABLES_TEMPLATEEXAMPLE_H
