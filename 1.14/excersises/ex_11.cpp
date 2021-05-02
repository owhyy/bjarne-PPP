#include "ch14.h"

int main() {
  Simple_window win(Point{100, 100}, 800, 800, "Binary Tree");
  Binary_tree_square t(Point{300, 300}, 3, "ad");
  t.set_node_label("rrr", "32");
  t.set_color(Color::red);
  win.attach(t);
  win.wait_for_button();
}
