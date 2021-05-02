#include "ch14.h"

int main() {
  Simple_window win{Point{100, 100}, 600, 600, "Group"};

  Group g;
  Circle c{Point{100, 100}, 50};
  Rectangle r{Point{200, 200}}
  g.add(c);


}
