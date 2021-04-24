#include "std_lib_facilites.h"
struct Num {
  int min, max, median, mean;
};
Num numericf(const vector<int> &vec) {
  int sum = 0, cnt = vec.size();
  Num retval;
  retval.max = *max_element(vec.begin(), vec.end());
  retval.min = *min_element(vec.begin(), vec.end());
  sum = accumulate(vec.begin(), vec.end(), sum);
  retval.mean = sum / cnt;
  retval.median = (vec[vec.size() - 1] + 1) / 2;
  return retval;
}
