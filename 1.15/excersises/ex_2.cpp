
#include "ch15.h"

using namespace Graph_lib;

double slope(double x) { return x / 2; }

int main() {
  Simple_window win(Point{200, 100}, 600, 600, "Fct");

  Func f(slope, -10, 11, Point{300, 300});
  f.reset();

  f.set_function(slope);
  f.set_range(-10, 11);
  f.set_origin(300, 300);
  f.set_count(100);

  f.call_function();
  f.set_color(Color::red);


  win.attach(f);
  win.wait_for_button();
}
