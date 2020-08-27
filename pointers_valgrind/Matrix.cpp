#include "Matrix.h"



Matrix::Matrix(int local_n, int local_m)
{
  // rows
  n = local_n;
  // columns
  m = local_m;
  pp_matrix = new float * [n];
  for (int i = 0; i < n; i++)
  {
    pp_matrix[i] = new float[m];
  }
}

Matrix::Matrix(int local_n, int local_m, float** pp_data)
{
  n = local_n;
  m = local_m;
  pp_matrix = new float *[n];
  for (int i = 0; i < n; i++)
  {
      pp_matrix[i] = new float[m];
      for (int j = 0; j < m; j++)
      {
	pp_matrix[i][j] = pp_data[i][j];
      }
  }
}


/*
  There be many bugs here.  
 */
Matrix::Matrix(const Matrix & other_matrix)
{
  n = other_matrix.n;
  m = other_matrix.m;
  // what does this mean?
  // why is this a problem?
  pp_matrix = other_matrix.pp_matrix;
  // shallow copy.  (not a copy at all, pointing to the exact same data block)
}

Matrix & Matrix::operator + (const Matrix & other_matrix)
{
  Matrix * result = new Matrix(n, m);
  if (n == other_matrix.n && m == other_matrix.m)
  {
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
	result->pp_matrix[i][j] = pp_matrix[i][j] + other_matrix.pp_matrix[i][j];
      }
    }
  }
  return *result;
}

Matrix & Matrix::operator * (const Matrix & other_matrix)
{
  Matrix * result = new Matrix(n, other_matrix.m);
  if (m == other_matrix.n)
  {
    for (int i = 0; i < n; i++)
    {
      for (int k = 0; k < m; k++)
      {
	for(int j = 0; j < other_matrix.m; j++)
	{
	  result->pp_matrix[i][j] += pp_matrix[i][k] * other_matrix.pp_matrix[k][j];
	}
      }
    }
  }
  return *result;
}

Matrix & Matrix::operator = (const Matrix & other_matrix)
{
  n = other_matrix.n;
  m = other_matrix.m;
  // same mistake in here as well, this is a shallow copy. 
  pp_matrix = other_matrix.pp_matrix;
  return *this;
}

Matrix::~Matrix()
{
  delete pp_matrix;
}
