#include "ex_10.cpp"
#include "ex_2.cpp"
#include "ex_3.cpp"
#include "ex_4.cpp"
#include "ex_5.cpp"
#include "ex_6.cpp"
#include "ex_7.cpp"
#include "ex_8.cpp"
#include "ex_9.cpp"

void fr(const string &i) { cout<<i; }
void fnr(const string i) { cout<<i; }

int main() {
  vector<int> vec{1, 2, 3, 4, 5};
  vector<double> w{15.625, 20.5, 15.31, 25.991, 35, 13};
  vector<double> p{100.14, 23.84, 19, 91, 54.133, 18.32};
  vector<string> svec{"aa", "an", "ana", "are", "mere"};
  fr("ana");
  fnr("ana");
}
