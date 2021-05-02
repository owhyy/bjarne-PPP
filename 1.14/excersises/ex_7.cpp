#include "ch14.h"

int main() {
  Simple_window win{Point{100, 100}, 600, 600, "Striped Circle"};
  
  Pseudo_window pw(Point{100,100}, 400, 300);
  win.attach(pw);
  win.wait_for_button();
}
