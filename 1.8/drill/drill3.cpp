#include "std_lib_facilites.h"

namespace X {
int var;
void print() { cout << "x:" << var << '\n'; }
} // namespace X
namespace Y {
int var;
void print() { cout << "y:" << var << '\n'; }
} // namespace Y
namespace Z {
int var;
void print() { cout << "z:" << var << '\n'; }
} // namespace Z
int main() {
  X::var = 7;
  X::print();
  using namespace Y;
  var = 9;
  print();
  {
    using Z::print;
    using Z::var;
    var = 11;
    print();
  }
  print();
  X::print();
}
