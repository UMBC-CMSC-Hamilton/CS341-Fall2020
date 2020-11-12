#include <iostream>
#include <string>
using namespace std;
#include "TemplateExample.h"

int main() {
    TemplateExample<int> my_int_ex;
    TemplateExample<string> my_string_ex;
    my_int_ex.eat(5);
    my_int_ex.eat(7);
    my_int_ex.eat(12);
    try {
        cout << my_int_ex.spit_out() << endl;
    }
    catch (EmptyStack & es)
    {
        cout << "There was an empty stack exception thrown" << endl;
    }

    TemplateExample<int> my_int_ex_copy;
    my_int_ex_copy = my_int_ex;
    cout << my_int_ex_copy.spit_out();
    return 0;
}
