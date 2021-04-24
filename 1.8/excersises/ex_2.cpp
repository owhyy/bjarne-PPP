#include "ex_1.cpp"
#include "std_lib_facilites.h"
void fibonacci(int x, int y, vector<int>& v, vector<int>::size_type n) {
  v[0] = x;
  v[1] = y;
  for (int i = 2; i != n; ++i) {
    int new_val = x + y;
    x = y;
    y = new_val;
    v[i]=new_val;
  }
  print("fibonacci", v);
}
