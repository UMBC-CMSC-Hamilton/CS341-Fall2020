/*
2-D Array.  
 */

class Matrix
{
 public:
  Matrix(int n, int m);
  Matrix(int n, int m, float ** pp_data);
  Matrix(const Matrix & other_matrix);

  Matrix & operator + (const Matrix & other_matrix);
  Matrix & operator * (const Matrix & other_matrix);
  Matrix & operator = (const Matrix & other_matrix);
  ~Matrix();
 private:
  int n, m;
  float ** pp_matrix;
};
