#include "../GUI/GUI.h"
#include "../GUI/Graph.h"
#include "../GUI/Window.h"
#include <algorithm>
#include <map>
using namespace Graph_lib;

enum class Function_Type {
  one = 0,
  sin,
  cos,
  slope,
  sin_slope,
  sin_cos,
  sin_sq_cos_sq
};

double one(double) { return 1; }

struct My_window : public Graph_lib::Window {
  My_window(Point xy, int w, int h, const string &title);

private:
  // buttons
  Menu graph_types;
  Button select_parameters;
  In_box set_range_begin;
  In_box set_range_end;
  In_box set_count;
  In_box set_xscale;
  In_box set_yscale;

  // actions
  void select_parameters_pressed();
  void cos_button_pressed();
  void sin_button_pressed();
  void one_button_pressed();
  // other objects
  Function_Type f_type = Function_Type::one;
  /* Func func{[](double) { return 1; }, -11, 10, Point{x_max() / 2, y_max() /
   * 2}}; */
  /* Func func{one, -11, 10, Point{x_max() / 2, y_max() / 2}, 25, 25, 100, 1.0};
   */
  Func func;
};
My_window::My_window(Point xy, int w, int h, const string &title)
    : Window(xy, w, h, title), graph_types{Point{x_max() - 125, 50}, 115, 20,
                                           Menu::vertical, "Graph type"},
      select_parameters{
          Point{x_max() - 125, 0}, 115, 25, "Graph function!",
          [](Address, Address pw) {
            return reference_to<My_window>(pw).select_parameters_pressed();
          }},
      set_range_begin{Point{110, 0}, 100, 20, "Range begin: "},
      set_range_end{Point{300, 0}, 100, 20, "Range end "},
      set_count{Point{110, 40}, 100, 20, "Count : "}, set_xscale{Point{110, 20},
                                                                 100, 20,
                                                                 "x scale : "},
      set_yscale{Point{300, 20}, 100, 20, "y scale : "} {
  graph_types.attach(
      new Button{Point{0, 0}, 0, 0, "one", [](Address, Address pw) {
                   return reference_to<My_window>(pw).one_button_pressed();
                 }});

  graph_types.attach(
      new Button{Point{0, 0}, 0, 0, "sin", [](Address, Address pw) {
                   return reference_to<My_window>(pw).sin_button_pressed();
                 }});
  graph_types.attach(
      new Button{Point{0, 0}, 0, 0, "cos", [](Address, Address pw) {
                   return reference_to<My_window>(pw).cos_button_pressed();
                 }});

  attach(set_range_begin);
  attach(set_range_end);
  attach(set_count);
  attach(set_yscale);
  attach(set_xscale);
  attach(select_parameters);
  attach(graph_types);
  attach(func);
  /* func.set_color(Color::invisible); */
}

void My_window::select_parameters_pressed() {
  double r1 = set_range_begin.get_int();
  double r2 = set_range_end.get_int();
  int count = set_count.get_int();
  double xscale = set_xscale.get_int();
  double yscale = set_yscale.get_int();

  cout << r1 << ' ' << r2 << ' ' << count << ' ' << xscale << ' ' << yscale
       << ' ' << (int)f_type;

  /* switch (f_type) { */
  /* case Function_Type::one: */
  /*   func.set_function([](double) { return 1; }); */
  /*   break; */
  /* case Function_Type::sin: */
  /*   func.set_function([](double n) { return sin(n); }); */
  /*   break; */
  /* case Function_Type::cos: */
  /*   func.set_function([](double n) { return cos(n); }); */
  /*   break; */
  /* case Function_Type::slope: */
  /*   func.set_function([](double n) { return n / 2; }); */
  /*   break; */
  /* } */
  /* func.set_count(count); */
  /* func.set_range(r1, r2); */
  /* func.set_origin(x_max() / 2, y_max() / 2); */
  /* func.set_scaling(xscale, yscale); */
  /* func.set_color(Color::black); */
  redraw();
}
void My_window::one_button_pressed() { f_type = Function_Type::one; }
void My_window::sin_button_pressed() { f_type = Function_Type::sin; }
void My_window::cos_button_pressed() { f_type = Function_Type::cos; }
int main() {
  ifstream file("currencies.txt");
  My_window win{Point{100, 100}, 600, 400, "My window"};
  return gui_main();
}
