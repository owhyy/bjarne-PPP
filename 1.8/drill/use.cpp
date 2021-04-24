#include "my.cpp"
#include "my.h"
int main() {
  int x = 7;
  int y = 9;
  swap_v(x, y);
  swap_r(x, y);
  swap_cr(x, y);
  swap_v(7, 9);
  swap_r(7, 9);
  swap_cr(7, 9);
  const int cx = 7;
  const int cy = 9;
  swap_v(cx, cy);
  swap_r(cx, cy);
  swap_cr(cx, cy);

  swap_v(7.7, 9.9);
  swap_r(7.7, 9.9);
  swap_cr(7.7, 9.9);

  double dx=7.7;
  double dy=9.9;

  swap_v(dx, dy);
  swap_r(dx, dy);
  swap_cr(dx, dy);
  
  swap_v(7.7, 9.9);
  swap_r(7.7, 9.9);
  swap_cr(7.7, 9.9);
}
