
#include <iostream>
using namespace std;

int factr(int n) { return n < 1 ? n : n * factr(n - 1); }

int facti(int n) {

  int r = 1;
  while (n > 0) {
    r *= n;
    n--;
  }
  return r;
}

int main() {
  for (int i = 0; i <= 20; ++i)
    cout << facti(i) << '\n';
  
  cout<<"\n\n";
  for (int i = 0; i <= 20; ++i)
    cout << factr(i) << '\n';
}
