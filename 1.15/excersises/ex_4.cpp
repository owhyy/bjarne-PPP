#include "../GUI/Graph.h"
#include "../GUI/Simple_window.h"
using namespace Graph_lib;

double term(int n)
// provide the appropriate Leibniz term w/correct sign
{
  int denom = 2 * n + 1;
  denom *= n % 2 == 0 ? 1 : -1;

  return 1.0 / denom;
}
double leibniz(int n) {
  double s = 0;
  for (int i = 0; i != n; ++i)
    s += term(i);
  return s;
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

  for (int i = 0; i != 20; ++i) {
    Function f([i](double) { return leibniz(i); }, r_min, r_max, origin, count,
               x_scale, y_scale);
    win.attach(f);
    win.wait_for_button();
    win.detach(f);
  }
  win.wait_for_button();
}
