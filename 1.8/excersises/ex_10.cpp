#include "algorithm"
#include "std_lib_facilites.h"
vector<int> charsizes(const vector<string> &svec) {
  vector<int> ret;
  for (auto i : svec)
    ret.push_back(i.size());
  return ret;
}
void string_op(const vector<string> &svec) {
  auto shortest = min_element(
      svec.begin(), svec.end(),
      [](const string &s1, const string &s2) { return s1.size() < s2.size(); });
  auto last =
      min_element(svec.begin(), svec.end(),
                  [](const string &s1, const string &s2) { return s1 < s2; });
  auto longest = max_element(
      svec.begin(), svec.end(),
      [](const string &s1, const string &s2) { return s1.size() < s2.size(); });
  auto first =
      max_element(svec.begin(), svec.end(),
                  [](const string &s1, const string &s2) { return s1 < s2; });
  cout << "shortest string: " << *shortest << '\n';
  cout << "longest string: " << *longest << '\n';
  cout << "first lexicografic string: " << *first << '\n';
  cout << "last lexicografic string: " << *last << '\n';
}
