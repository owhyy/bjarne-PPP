#include "ex_3.h"
vector<int> rev1(const vector<int> &vec)
{
  vector<int> returned(vec.rbegin(), vec.rend());
  return returned;
}
void rev2(vector<int> &vec)
{
  for(auto it = vec.begin(), rit = vec.end()-1; it!=rit; ++it, --rit)
    iter_swap(it, rit);
}
