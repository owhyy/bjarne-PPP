#include "ex_4.h"
vector<string> rev1(const vector<string> &vec)
{
  vector<string> returned(vec.crbegin(), vec.crend());
  return returned;
}
void rev2(vector<string> &vec)
{
  for(auto it = vec.begin(), rit=vec.end()-1; it!=rit; ++it, --rit)
    iter_swap(it, rit);
}

