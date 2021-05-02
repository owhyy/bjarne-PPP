#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ifstream ifs{"new-height-data.txt"};
  int height;
  vector<int> n_number;
  vector<int> n_height;
  int number;
  while (ifs >> number >> height) {
    n_number.push_back(number);
    n_height.push_back(height);
  }
  sort(n_number.begin(), n_number.end());
  sort(n_height.begin(), n_height.end());
  
  for (auto it = n_number.begin(); it != n_number.end(); ++it) {
    auto last = unique(it, n_number.end());
    n_number.erase(last, n_number.end());
  }
  for (auto it = n_height.begin(); it != n_height.end(); ++it) {
    auto last = unique(it, n_height.end());
    n_height.erase(last, n_height.end());
  }

  ofstream ofs("height-data.txt");
  for(int i = 0; i!=n_number.size(); ++i)
    ofs<<n_number[i]<<' '<<n_height[i]*2<<'\n';
}
