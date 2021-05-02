#include "../GUI/Graph.h"
#include "../GUI/Simple_window.h"
using namespace Graph_lib;

double sin_plus_cos(double x) { return sin(x) + cos(x); }
double sin_plus_cos_squared(double x) {
  return pow(sin(x), 2) + pow(cos(x), 2);
}

int main() {
  Simple_window win(Point{100, 100}, 800, 600, "sin, cos, sin+cos, sincos^2");

  constexpr int x_max = 800;
  constexpr int y_max = 600;

  constexpr int x_length = x_max - 40;
  constexpr int y_length = y_max - 40;

  constexpr int x_origin = x_max / 2;
  constexpr int y_origin = y_max / 2;
  Point origin{x_origin, y_origin};

  constexpr double r_min = -10;
  constexpr double r_max = 11;

  constexpr uint count = 400;

  constexpr double x_scale = 40;
  constexpr double y_scale = 40;

  Axis x(Axis::x, Point{20, y_origin}, x_length, x_length / x_scale,
         "1 notch == 1");
  Axis y(Axis::y, Point{x_origin, y_length + 20}, y_length, y_length / y_scale,
         "1 notch == 1");

  x.set_color(Color::red);
  y.set_color(Color::red);
  win.attach(x);
  win.attach(y);

  Function f1(sin, r_min, r_max, origin, count, x_scale, y_scale);
  f1.set_color(Color::dark_green);  
  win.attach(f1);
  
  Function f2(cos, r_min, r_max, origin, count, x_scale, y_scale);
  f2.set_color(Color::blue);  
  win.attach(f2);
  
  Function f3(sin_plus_cos, r_min, r_max, origin, count, x_scale, y_scale);
  win.attach(f3);
  
  Function f4(sin_plus_cos_squared, r_min, r_max, origin, count, x_scale, y_scale);
  f4.set_color(Color::dark_red);
  win.attach(f4);

  win.wait_for_button();
}
