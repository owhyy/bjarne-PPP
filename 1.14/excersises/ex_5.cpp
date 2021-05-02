
#include "ch14.h"

int main()
{
  Simple_window win{Point{100, 100}, 600, 600, "Striped Rectangle"};

  Striped_rectangle sr{Point{100, 100}, 100, 100};
  sr.set_fill_color(Color::black);
  win.attach(sr);
  win.wait_for_button();
}

