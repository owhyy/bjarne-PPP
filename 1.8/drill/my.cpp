#include "my.h"
#include "std_lib_facilites.h"
int foo;

void print_foo()
{
  cout<<foo;
}
void print(int i)
{
  cout<<i;
}
void swap_v(int a, int b)
{
  int temp; temp = a; a=b; b = temp;
}
void swap_r(int &a, int &b)
{
  int temp; temp = a; a=b; b = temp;
}
void swap_cr(const int &a, const int &b)
{
  int temp; temp = a; a=b; b = temp;
}
