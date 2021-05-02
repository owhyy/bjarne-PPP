#include "ch14.h"

int main() {
  Simple_window win{Point{100, 100}, 600, 600, "Regular Octagon"};

  Regular_octagon ro{50, Point{100, 100}};

  ro.move(50, 50);

  ro.set_color(Color::red);
  ro.set_fill_color(Color::black);
  cout << ro.number_of_points();
  win.attach(ro);

  win.wait_for_button();
}
