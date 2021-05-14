#include "../GUI/GUI.h"
#include "../GUI/Graph.h"
#include "../GUI/Window.h"

using namespace Graph_lib;

struct My_window : Graph_lib::Window {
  My_window(Point xy, int w, int h, const string &t);

private:
  // buttons
  Menu shape_menu;
  In_box next_x;
  In_box next_y;
  // other objects
  Circle c{Point{50, 50}, 50};
  Rectangle r{Point{0, 0}, Point{100, 100}};
  Polygon tr{Point{50, 50}, Point{-50, 150}, Point{150, 150}};
  Regular_hexagon p{Point{0, 0}, 50};
  // actions
  void reset(Shape &s) { s.move(-s.point(0).x, -s.point(0).y); }
  void circle_button_pressed();
  void square_button_pressed();
  void triangle_button_pressed();
  void hexagon_button_pressed();
};

My_window::My_window(Point xy, int w, int h, const string &t)
    : Window{xy, w, h, t}, shape_menu(Point{x_max() - 200, 100}, 200, 50,
                                      Menu::vertical, "Shape Menu"),
      next_x(Point{80, 5}, 80, 20, "x:"), next_y(Point{200, 5}, 80, 20, "y:") {
  shape_menu.attach(
      new Button{Point{0, 0}, 0, 0, "Circle",
                 [](Address, Address pw) {
                   return reference_to<My_window>(pw).circle_button_pressed();
                 }}),
      shape_menu.attach(new Button{
          Point{0, 0}, 0, 0, "Square",
          [](Address, Address pw) {
            return reference_to<My_window>(pw).square_button_pressed();
          }}),
      shape_menu.attach(new Button{
          Point{0, 0}, 0, 0, "Triangle",
          [](Address, Address pw) {
            return reference_to<My_window>(pw).triangle_button_pressed();
          }}),
      shape_menu.attach(new Button{
          Point{0, 0}, 0, 0, "Hexagon", [](Address, Address pw) {
            return reference_to<My_window>(pw).hexagon_button_pressed();
          }});
  attach(c);
  attach(r);
  attach(tr);
  attach(p);
  c.set_color(Color::invisible);
  r.set_color(Color::invisible);
  tr.set_color(Color::invisible);
  p.set_color(Color::invisible);
  attach(shape_menu);
  attach(next_x);
  attach(next_y);
}

void My_window::circle_button_pressed() {
  redraw();
  reset(c);
  int x = next_x.get_int();
  int y = next_y.get_int();
  c.move(x, y);
  c.set_color(Color::black);
  r.set_color(Color::invisible);
  tr.set_color(Color::invisible);
  p.set_color(Color::invisible);
}
void My_window::square_button_pressed() {
  redraw();
  reset(r);
  int x = next_x.get_int();
  int y = next_y.get_int();
  r.move(x, y);
  r.set_color(Color::black);
  c.set_color(Color::invisible);
  tr.set_color(Color::invisible);
  p.set_color(Color::invisible);
}

void My_window::triangle_button_pressed() {
  redraw();
  reset(tr);
  int x = next_x.get_int();
  int y = next_y.get_int();
  tr.move(x, y);
  tr.set_color(Color::black);
  c.set_color(Color::invisible);
  r.set_color(Color::invisible);
  p.set_color(Color::invisible);
}

void My_window::hexagon_button_pressed() {
  redraw();
  reset(p);
  int x = next_x.get_int();
  int y = next_y.get_int();
  p.move(x, y);
  p.set_color(Color::black);
  c.set_color(Color::invisible);
  r.set_color(Color::invisible);
  tr.set_color(Color::invisible);
}
int main() {
  My_window win{Point{100, 100}, 600, 400, "My window"};
  return gui_main();
}
