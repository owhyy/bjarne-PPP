#include "../GUI/Graph.h"
#include "../GUI/Point.h"
#include "../GUI/Simple_window.h"
#include "../GUI/ch13.h"
#include "../GUI/std_lib_facilities.h"
using namespace Graph_lib;

int main() {
  Simple_window win(Point{100, 100}, 600, 600, "TEST");
  Circle c1{Point{300, 300}, 200};
  Circle c2{Point{c1.center().x - c1.radius() / 3,
                  c1.center().y / 2 - c1.radius() / 3},
            c1.radius() / 4};
  Circle c3{Point{c1.center().x + c1.radius() / 3,
                  c1.center().y / 2 - c1.radius() / 3},
            c1.radius() / 4};
  Arc a{Point{c1.center().x, c1.center().y}, c1.radius() * 2 / 3, 200, 340};
  win.attach(c1);
  win.attach(c2);
  win.attach(c3);
  win.attach(a);
  win.wait_for_button();
}
