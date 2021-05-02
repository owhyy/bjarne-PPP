#include "../GUI/Graph.h"
#include "../GUI/Simple_window.h"

using namespace Graph_lib;

double slope(double x) { return x / 2; }
double square(double x) { return x * x; }
double sloping_cos(double x) { return slope(x) + cos(x); }
int main() {
  Simple_window win(Point{100, 100}, 600, 600, "Function Graphics");

  constexpr int x_max = 600;
  constexpr int y_max = 600;

  constexpr int r_min = -10;
  constexpr int r_max = 11;

  constexpr int x_orig = x_max / 2;
  constexpr int y_orig = y_max / 2;

  constexpr int x_scale = 20;
  constexpr int y_scale = 20;

  Point origin{x_orig, y_orig};

  constexpr int axis_length = 400;
  constexpr int number_of_notches = 400 / 20;
  Point intersection{300, 300};

  Axis x(Axis::x, Point{x_orig - 400 / 2, y_orig}, 400, number_of_notches,
         "1 == 20 pixels");
  Axis y(Axis::y, Point{300, y_orig + 400 / 2}, 400, number_of_notches);
  Mark m(intersection, 'x');

  Function f1([](double x) { return 1; }, r_min, r_max, origin, 400, x_scale,
              y_scale);

  Function f2(slope, r_min, r_max, origin, 400, x_scale, y_scale);
  Text f2_text(Point{x_orig - 450 / 2, y_orig + 120}, "x/2");

  /* Function f3(cos, r_min, r_max, origin, 400, x_scale, y_scale); */
  /* f3.set_color(Color::blue); */

  Function f4(cos, r_min, r_max, origin, 400, x_scale, y_scale);

  x.set_color(Color::red);
  y.set_color(Color::red);
  win.attach(x);
  win.attach(y);
  win.attach(m);
  win.attach(f1);
  win.attach(f2);
  win.attach(f2_text);
  /* win.attach(f3); */
  win.attach(f4);
  win.wait_for_button();
}
