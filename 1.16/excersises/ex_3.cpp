#include "../GUI/GUI.h"
#include "../GUI/Graph.h"
#include "../GUI/Window.h"
#include <random>

using namespace Graph_lib;
Menu;
inline int rand_int(int min, int max) {
  static default_random_engine ran;
  return uniform_int_distribution<>{min, max}(ran);
}
struct My_window : Graph_lib::Window {
  My_window(Point xy, int w, int h, const string &t);

private:
  // buttons
  Button button_1;
  // other objects
  Image img{Point{x_max() - 350, y_max() / 2 - 50}, "img_txt/img.jpeg"};
  // actions
  void button1_pressed();
};

My_window::My_window(Point xy, int w, int h, const string &t)
    : Window{xy, w, h, t}, button_1{
                               Point{x_max() - 350, y_max() / 2 - 50}, 150, 50,
                               " ", [](Address, Address pw) {
                                 reference_to<My_window>(pw).button1_pressed();
                               }} {
  attach(button_1);
  img.set_mask(Point{175, 200}, 150, 50);
  attach(img);
}

void My_window::button1_pressed() {
  int dx = rand_int(-20, 20);
  int dy = rand_int(-20, 20);
  img.move(dx, dy);
  button_1.move(dx, dy);
  /* redraw(); */
}

int main() {
  My_window win{Point{100, 100}, 600, 400, "My window"};
  return gui_main();
}
