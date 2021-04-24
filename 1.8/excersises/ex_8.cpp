#include "std_lib_facilites.h"
int maxv(const vector<int> &vec)
{
  int max=vec[0];
  for(int i = 0; i!=vec.size(); ++i)
    if(max<vec[i])
      max=vec[i];
  return max;
}
