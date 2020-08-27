#include <iostream>
#include "Matrix.h"

using namespace std;

void assignment_operator()
{
  // non-dynamic array.  Allocated as soon as the function starts.  In the "stack"
  float two_d[2][2] = { {1, 2}, {2, 3} };
  // what is the difference? dynamic array "heap"
  //  float * blah = new float[4];
  // it's not declared, not allocated until your program runs.  
  Matrix m_1 = Matrix(2, 2, (float**)two_d);
  // remember pp_matrix = other_thingy.pp_matrix;
  Matrix m_2 = m_1;
  //  delete [] blah;
}

int main()
{
  assignment_operator();  
  
}
