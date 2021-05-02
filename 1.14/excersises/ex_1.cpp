
#include "ch14.h"

int main(){
  Simple_window win(Point{100, 100}, 800, 800, "Smiley/Frowney");

  Smiley_hat hs{Point{300, 300}, 100};
  win.attach(hs);
  
  Frowny_hat hf{Point {500, 300}, 100};
  win.attach(hf);
  
  win.wait_for_button();
}
