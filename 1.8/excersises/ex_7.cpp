#include "std_lib_facilites.h"
double sum_index(const vector<double> &price, const vector<double> &weight) {
  if (price.size() != weight.size())
    error("Different sizes. Please re-check your vectors\n");
  vector<double> index(weight.size());
  for (int i = 0; i != price.size(); ++i) {
    index[i] = price[i] * weight[i];
  }
  return accumulate(index.begin(), index.end(), 0.0f);
}
