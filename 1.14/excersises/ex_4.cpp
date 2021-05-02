
#include "ch14.h"

int main() {
  Simple_window win{Point{100, 100}, 600, 600, "Immobile Circle"};

  Immobile_circle ic{Point{100, 100}, 50};
  ic.move(10, 10);

  win.wait_for_button();
}
