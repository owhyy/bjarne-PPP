#include "ch14.h"

int main() {
  Simple_window win{Point{100, 100}, 600, 600, "Striped Circle"};

  Striped_circle c{Point{100, 100}, 100};
  c.set_fill_color(Color::blue);
  win.attach(c);
  win.wait_for_button();
}
