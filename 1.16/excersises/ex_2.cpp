#include "../GUI/GUI.h"
#include "../GUI/Window.h"
#include <memory>
using namespace Graph_lib;
struct My_window : Graph_lib::Window {
  My_window(Point xy, int w, int h, const string &t);

private:
  // buttons
  Button next_button;
  Button quit_button;
  Button button_1;
  Button button_2;
  /* Button button_3; */
  /* Button button_4; */
  Out_box coord_box;

  // other objects
  Rectangle r;
  // actions
  void next_pressed();
  void quit_pressed();
  void button1_pressed();
  void button2_pressed();
  void button3_pressed();
  void button4_pressed();
};

My_window::My_window(Point xy, int w, int h, const string &t)
    : Window{xy, w, h, t},
      next_button{Point{x_max() - 50, 20}, 50, 20, "Next",
                  [](Address, Address pw) {
                    reference_to<My_window>(pw).next_pressed();
                  }},
      quit_button{Point{x_max() - 50, 40}, 50, 20, "Quit",
                  [](Address, Address pw) {
                    reference_to<My_window>(pw).quit_pressed();
                  }},
      button_1{Point{x_max() - 450, y_max() / 2 - 50}, 150, 50, "Press me!",
               [](Address, Address pw) {
                 reference_to<My_window>(pw).button1_pressed();
               }},
      button_2{Point{x_max() - 300, y_max() / 2 - 50}, 150, 50, "Press me!",
               [](Address, Address pw) {
                 reference_to<My_window>(pw).button2_pressed();
               }},
      /* button_3{Point{x_max()-400, y_max()/2}, 150, 100, "Press me!",
         [](Address, Address
         pw){reference_to<My_window>(pw).button3_pressed();}}, */
      /* button_4{Point{x_max()-250, y_max()/2}, 150, 100, "Press me!",
         [](Address, Address
         pw){reference_to<My_window>(pw).button4_pressed();}}, */
      coord_box{Point{x_max() - 500, y_max() / 2 - 50}, 150, 50, "Coordinates"},
      r{Point{x_max() - 300, y_max() / 2 - 50}, 150, 50} {
  attach(next_button);
  attach(quit_button);
  attach(button_1);
  attach(button_2);
  /* attach(button_3); */
  /* attach(button_4); */
  attach(coord_box);
  r.set_fill_color(Color::invisible);
  r.set_color(Color::invisible);
  coord_box.hide();
}

void My_window::next_pressed() { redraw(); }
void My_window::quit_pressed() { hide(); }
void My_window::button1_pressed() {
  button_1.hide();
  button_2.show();
  coord_box.put(to_string(x_max() - 400) + ' ' + to_string(y_max() / 2));
  coord_box.show();
}
void My_window::button2_pressed() {
  r.set_fill_color(Color::blue);
  coord_box.hide();
  button_1.show();
  attach(r);
  button_2.hide();
}
/* void My_window::button3_pressed(){} */
/* void My_window::button4_pressed(){} */

int main() {
  My_window win{Point{100, 100}, 600, 400, "My window"};
  return gui_main();
}
