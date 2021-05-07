#include "../GUI/GUI.h"
#include "../GUI/Graph.h"

using namespace Graph_lib;

struct Lines_window : Graph_lib::Window {
  Lines_window(Point xy, int w, int h, const string &title);

private:
  // data
  Open_polyline lines;

  // widgets
  Menu style_menu;
  Button style_menu_button;
  Menu color_menu;
  Button color_menu_button;
  Button next_button;
  Button quit_button;
  Button weight_button;
  In_box line_weight;
  In_box next_x;
  In_box next_y;
  Out_box xy_out;
   
  void change_style(Line_style s) {lines.set_style(s);}
  void change_color(Color c) { lines.set_color(c); }

  void hide_color_menu() {
    color_menu.hide();
    color_menu_button.show();
  }

  void hide_styles_menu(){
    style_menu.hide();
    style_menu_button.show();
  }

  // actions invoked by callbacks
  void red_pressed() { change_color(Color::red); }
  void blue_pressed() { change_color(Color::blue); }
  void black_pressed() { change_color(Color::black); }
  void color_menu_pressed() {
    color_menu_button.hide();
    color_menu.show();
  }
  void style_menu_pressed(){
    style_menu_button.hide();
    style_menu.show();
  }
  void solid_pressed() {change_style(Line_style::solid);}
  void dotted_pressed() {change_style(Line_style::dot);}
  void dashed_pressed() {change_style(Line_style::dash);}
  void dash_dot_pressed() {change_style(Line_style::dashdot);}
  void dash_dot_dot_pressed() {change_style(Line_style::dashdotdot);}
  void set_lw();
  void next();
  void quit();
  static void cb_red(Address, Address pw){reference_to
    <Lines_window>(pw).red_pressed();};
  static void cb_blue(Address, Address pw){reference_to
    <Lines_window>(pw).blue_pressed();};
  static void cb_black(Address, Address pw){reference_to
    <Lines_window>(pw).black_pressed();};
  static void cb_color_menu(Address, Address pw) {
    reference_to<Lines_window>(pw).color_menu_pressed();
  };

  static void cb_next(Address, Address pw){reference_to
    <Lines_window>(pw).next();};
  static void cb_quit(Address, Address pw){reference_to
    <Lines_window>(pw).quit();};
  static void cb_solid(Address, Address pw){reference_to
    <Lines_window>(pw).solid_pressed();};
  static void cb_dot(Address, Address pw){reference_to
    <Lines_window>(pw).dotted_pressed();};
  static void cb_dash(Address, Address pw){reference_to
    <Lines_window>(pw).dashed_pressed();};
  static void cb_dashdot(Address, Address pw){reference_to
    <Lines_window>(pw).dash_dot_pressed();};
  static void cb_dashdotdot(Address, Address pw){reference_to
    <Lines_window>(pw).dash_dot_dot_pressed();};
  static void cb_style_menu(Address, Address pw){reference_to
    <Lines_window>(pw).style_menu_pressed();};
  static void cb_weight(Address, Address pw){reference_to
    <Lines_window>(pw).set_lw();};

};
  Lines_window::Lines_window(Point xy, int w, int h, const string &title)
      : Window{xy, w, h, title}, next_button{Point{x_max() - 150, 0}, 70, 20,
                                             "Next point", cb_next},
        quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit", cb_quit},
        next_x{Point{x_max() - 310, 0}, 50, 20, "next x:"},
        next_y{Point{x_max() - 210, 0}, 50, 20, "next y:"},
        xy_out{Point{100, 0}, 100, 20, "current(x,y):"},
        weight_button{Point{x_max()-70, 265}, 70, 20, "select", cb_weight},
        color_menu{Point{x_max() - 70, 40}, 70, 20, Menu::vertical, "color"},
        color_menu_button{Point{x_max() - 80, 30}, 80, 20, "color menu",
                          cb_color_menu},
        style_menu{Point{x_max()-70, 120}, 70, 20, Menu::vertical, "style"},
        style_menu_button{Point{x_max()-80, 110}, 80, 20, "style menu", cb_style_menu},
        line_weight{Point{x_max()-70, 240}, 70, 20, "line weight:"}

{
    attach(next_button);
    attach(quit_button);
    attach(next_x);
    attach(next_y);
    attach(line_weight);
    attach(weight_button);
    attach(xy_out);
    xy_out.put("no point");
    color_menu.attach(new Button{Point{0, 0}, 0, 0, "red", cb_red});
    color_menu.attach(new Button{Point{0, 0}, 0, 0, "blue", cb_blue});
    color_menu.attach(new Button{Point{0, 0}, 0, 0, "black", cb_black});
    attach(color_menu);
    color_menu.hide();
    attach(color_menu_button);
    style_menu.attach(new Button{Point{0,0}, 0,0, "solid", cb_solid});
    style_menu.attach(new Button{Point{0,0}, 0,0, "dot", cb_dot});
    style_menu.attach(new Button{Point{0,0}, 0,0, "dash", cb_dash});
    style_menu.attach(new Button{Point{0,0}, 0,0, "dash dot", cb_dashdot});
    style_menu.attach(new Button{Point{0,0}, 0,0, "dash dot dot", cb_dashdotdot});
    attach(style_menu);
    style_menu.hide();
    attach(style_menu_button);
    attach(lines);
  }

void Lines_window::quit() { hide(); }
void Lines_window::next() {
  int x = next_x.get_int();
  int y = next_y.get_int();
  lines.add(Point{x, y});

  ostringstream ss;
  ss << '(' << x << ',' << y << ')';
  xy_out.put(ss.str());

  redraw();
}
void Lines_window::set_lw(){
  int w = line_weight.get_int();
  int old_ls =lines.style_as_int();
  Line_style ls = Line_style(static_cast<Line_style::Line_style_type>(old_ls), w);
  lines.set_style(ls);
}
int main() {
  Lines_window win{Point{100, 100}, 600, 400, "lines"};
  return gui_main();
}
