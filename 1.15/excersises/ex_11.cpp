#include "ch15.h"
#include <algorithm>
#include <cctype>
using namespace Graph_lib;

struct Climates {
  int month;
  int frk;  // Frankfurt
  int auck; // Auckland
  int stcz; // Santa Cruz
};
struct Scale {
  int cbase;
  int vbase;
  double scale;
  Scale(int b, int vb, double s) : cbase{b}, vbase{vb}, scale{s} {}
  int operator()(int v) const { return cbase + (v - vbase) * scale; }
};
istream &operator>>(istream &is, Climates &c) {
  char ch = 0;
  Climates cc;
  is >> cc.month;
  is >> cc.frk;
  is >> cc.auck;
  is >> cc.stcz;
  c = cc;
  return is;
}
int main() {

  ifstream ifs("climate.txt");
  constexpr int base_month = 1;
  constexpr int end_month = 12;

  constexpr int xmax = 800;
  constexpr int ymax = 600;

  constexpr int xoffset = 100;
  constexpr int yoffset = 60;

  constexpr int xspace = 40;
  constexpr int yspace = 40;

  constexpr int xlength = xmax - xoffset - xspace;
  constexpr int ylength = ymax - yoffset - yspace;

  constexpr double xscale =
      double(xlength) / (end_month - base_month); // months
  constexpr double yscale = double(ylength) / 40; // temperatures

  Scale xs{xoffset, base_month, xscale};
  Scale ys{ymax - yoffset, 0, -yscale};

  Simple_window win(Point{100, 100}, xmax, ymax, "Graph");

  Axis x{Axis::x, Point{xoffset, ymax - yoffset}, xlength, (12),
         "month           1           2           3             4             "
         "5             6             7             8             9          "
         "10         11           12"};
  x.label.move(-300, 0);
  Axis y{Axis::y, Point{xoffset, ymax - yoffset}, ylength, 8,
         "Average highest temperature"};

  Open_polyline frankfurt;
  Open_polyline auckland;
  Open_polyline santa_cruz;

  for (Climates c; ifs >> c;) {
    const int x = xs(c.month);
    frankfurt.add(Point{x, ys(c.frk)});
    auckland.add(Point{x, ys(c.auck)});
    santa_cruz.add(Point{x, ys(c.stcz)});
  }

  Text frk_label{Point{20, frankfurt.point(0).y}, "Frankfurt"};
  Text auck_label{Point{20, auckland.point(0).y}, "Auckland"};
  Text stcz_label{Point{20, santa_cruz.point(0).y}, "Santa-Cruz"};

  frankfurt.set_color(Color::red);
  auckland.set_color(Color::dark_yellow);
  santa_cruz.set_color(Color::blue);
  frk_label.set_color(Color::red);
  auck_label.set_color(Color::dark_yellow);
  stcz_label.set_color(Color::blue);

  win.attach(frk_label);
  win.attach(auck_label);
  win.attach(stcz_label);
  win.attach(frankfurt);
  win.attach(auckland);
  win.attach(santa_cruz);
  win.attach(x);
  win.attach(y);
  win.wait_for_button();
}
