
#include "ch14.h"
using namespace Graph_lib;
struct Controller {
  void virtual on() = 0;
  void virtual off() = 0;
  void virtual set_level(int) = 0;
  void virtual show() const = 0;

protected:
  int level = 0;
  bool status = false;
  Controller() {}
};

struct Test_Controller : Controller {
  Test_Controller() {}
  Test_Controller(int l, bool s) : level{l}, status{s} {}
  void on() { status = true; }
  void off() { status = false; }
  void set_level(int l) { level = l; }
  void show() const;

private:
  int level = 0;
  bool status = false;
};
void Test_Controller::show() const {
  cout << level << '\n';
  cout << (status == 0 ? "Off" : "On") << '\n';
}

struct Switch : Controller {
  Switch() {}
  Switch(Shape &ss) : s{&ss} {}
  void on() {
    status = true;
    s->set_fill_color(Color::white);
    s->set_color(Color::white);
  }
  void off() {
    status = false;
    s->set_color(Color::black);
  }
  void set_level(int l) {
    level = l;
    s->set_style(Line_style(Line_style::solid, l));
  }
  void show() const;

private:
  Shape *s;
};
void Switch::show() const {
  if (status)
    cout << "Light is turned on\n";
  else
    cout << "Light is turned off\n";
  cout << "Shape is at level " << level << '\n';
}
int main() {
  Simple_window win(Point{100, 100}, 600, 600, "Controller");

  Rectangle r{Point{100, 100}, 10, 10};

  Switch tc(r);
  tc.on();
  tc.show();
  win.attach(r);
  win.wait_for_button();
}
