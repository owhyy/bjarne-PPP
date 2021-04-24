#include "ex_1.h"
void print(const string &str, const vector<int> &vec) {
  cout << "Currently printing the vector " << str << '\n';
  for (const auto &i : vec)
    cout << i << ' ';
  cout<<'\n';
}

void print(const string &str, const vector<string> &vec) {
  cout << "Currently printing the vector " << str << '\n';
  for (const auto &i : vec)
    cout << i << ' ';
  cout<<'\n';
}
