#include "../GUI/GUI.h"
#include "../GUI/Window.h"

using namespace Graph_lib;

struct My_window : Graph_lib::Window {
  My_window(Point xy, int w, int h,const string &t);

  private:
  Button next_button;
  Button quit_button;
  
  void next_pressed();
  void quit_pressed();

};

My_window::My_window(Point xy, int w, int h,const string& t) : Window{xy, w, h, t}, next_button{Point{x_max()-50, 20}, 50, 20, "Next", [](Address, Address pw){reference_to<My_window>(pw).next_pressed();}}, quit_button{Point{x_max()-50, 40}, 50, 20, "Quit", [](Address, Address pw){reference_to<My_window>(pw).quit_pressed();}}
{
  attach(next_button);
  attach(quit_button);
}

void My_window::next_pressed() {
  redraw(); 
}
void My_window::quit_pressed() {
 hide(); 
}

int main(){

  My_window win{Point{100,100}, 600,400, "My window"};
  return gui_main();
}
