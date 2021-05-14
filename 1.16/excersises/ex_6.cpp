#include "../GUI/GUI.h"
#include "../GUI/Graph.h"
#include "../GUI/Window.h"
#include <chrono>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <unistd.h>

constexpr double pi = 3.14159265;

using namespace Graph_lib;
class Clock : public Circle {
public:
  Clock(Point p, int rr);
  void draw_lines() const;
  void refresh();
  void increase_time();

private:
  Lines ticks;
  Vector_ref<Line> hands;
  int hh;
  int mm;
  int ss;
};

Clock::Clock(Point p, int rr) : Circle(p, rr), hh(0), mm(0), ss(0) {
  double inner_radius = 0.8 * rr;
  for (int i = 0; i != 12; ++i) {
    double angle = i * pi / 6;
    int tx1 = p.x + inner_radius * cos(pi / 2 - angle);
    int tx2 = p.x + rr * cos(pi / 2 - angle);
    int ty1 = p.y + inner_radius * sin(pi / 2 - angle);
    int ty2 = p.y + rr * sin(pi / 2 - angle);
    ticks.add(Point{tx1, ty1}, Point{tx2, ty2});
    ticks.set_style(Line_style(Line_style::solid, 1));
  }

  time_t t = time(0);
  struct tm *now = localtime(&t);
  hh = now->tm_hour;
  mm = now->tm_min;
  ss = now->tm_sec;

  double phi = (hh + mm / 60.0) / 6.0 * pi;
  int hx = round(p.x + 0.6 * rr * cos(pi / 2 - phi));
  int hy = round(p.y + 0.6 * rr * sin(-pi / 2 + phi));
  hands.push_back(new Line(p, Point{hx, hy}));
  hands[0].set_style(Line_style(Line_style::solid, 3));

  phi = mm / 30.0 * pi;
  hx = round(p.x + 0.9 * rr * cos(pi / 2 - phi));
  hy = round(p.y + 0.9 * rr * sin(-pi / 2 + phi));
  hands.push_back(new Line(p, Point{hx, hy}));
  hands[1].set_style(Line_style(Line_style::solid, 3));

  phi = ss / 30.0 * pi;
  hx = round(p.x + 0.9 * rr * cos(pi / 2 - phi));
  hy = round(p.y + 0.9 * rr * sin(-pi / 2 + phi));
  hands.push_back(new Line(p, Point{hx, hy}));
  hands[2].set_style(Line_style(Line_style::solid, 2));
  hands[2].set_color(Color::red);
}

void Clock::draw_lines() const {
  Circle::draw_lines();
  ticks.draw();
  for (int i = 0; i != 3; ++i)
    hands[i].draw();
}

void Clock::increase_time() {
  ++ss;
  if (ss == 60) {
    ++mm;
    ss = 0;
    if (mm == 60) {
      ++hh;
      mm = 0;
      if (hh == 12)
        hh = 0;
    }
  }
}

void Clock::refresh() {
  double tick = 3600 * hh + 60 * mm + ss;
  double sec_tick = pi / ((30 * pi) / 180) / tick;
  int deg = tick * pi / 30 - pi / 2;
  /* double min_tick = pi / ((1800 * pi) / 180) / tick; */
  /* double hour_tick = pi / ((21600 * pi) / 180) / tick; */
  Point p = center();
  int rr = radius();
  /* int hx = round(p.x + 0.6 * rr * cos(pi / 2 - sec_tick)); */
  /* int hy = round(p.y + 0.6 * rr * sin(-pi / 2 + sec_tick)); */
  int initial_sec = sec_tick * pi / 2;
  int a1 = p.x - rr * sin(sec_tick);
  int a2 = p.y - rr * cos(sec_tick);
  cout << a2;
  /* hands[0].point(1) = Point{hx, hy}; */
}

/* void Clock::refresh() { */

/*   double phi = (hh + mm / 60.0) / 6.0 * pi; */
/*   Point p = center(); */
/*   int rr = radius(); */
/*   cout << rr; */
/*   int hx = round(p.x + 0.6 * rr * cos(pi / 2 - phi)); */
/*   int hy = round(p.y + 0.6 * rr * sin(-pi / 2 + phi)); */
/*   hands[0].point(1) = Point{hx, hy}; */

/*   phi = mm / 30.0 * pi; */
/*   hx = round(p.x + 0.9 * rr * cos(pi / 2 - phi)); */
/*   hy = round(p.y + 0.9 * rr * sin(-pi / 2 + phi)); */
/*   hands.push_back(new Line(p, Point{hx, hy})); */
/*   hands[1].point(1) = Point{hx, hy}; */

/*   phi = ss / 30.0 * pi; */
/*   hx = round(p.x + 0.9 * rr * cos(pi / 2 - phi)); */
/*   hy = round(p.y + 0.9 * rr * sin(-pi / 2 + phi)); */
/*   hands.push_back(new Line(p, Point{hx, hy})); */
/*   hands[2].point(1) = Point{hx, hy}; */
/* } */

inline int rand_int(int min, int max) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);

  return std::uniform_int_distribution<int>{min, max}(generator);
}

class TimerC : public Graph_lib::Widget {
private:
  double time_interval;
  int state; // working = 1, st,opped = 0

  static void call_back_timer(void *timerc) {
    static_cast<TimerC *>(timerc)->do_it(nullptr,
                                         static_cast<TimerC *>(timerc)->own);
    Fl::repeat_timeout(*static_cast<TimerC *>(timerc), call_back_timer, timerc);
  }

  void attach(Graph_lib::Window &win) { own = &win; }

public:
  // Constructor
  // time = time interval in seconds
  // cb = callback function
  // initial 1 = working at begin / initial 0 = stopped at begin
  TimerC(double time, Callback cb, int initial)
      : Graph_lib::Widget(Graph_lib::Point{0, 0}, 0, 0, "", cb),
        time_interval{time}, state{initial} {
    if (state)
      Fl::add_timeout(time_interval, call_back_timer, this);
  }

  // return time interval
  operator double() const { return time_interval; }

  // Setup interval
  void set_interval(const int i) { time_interval = i; }

  // Stop timer
  void stop() {
    if (state) {
      Fl::remove_timeout(call_back_timer, this);
      state = 0;
    }
  }

  // Start Timer
  void start() {
    if (!state) {
      Fl::add_timeout(time_interval, call_back_timer, this);
      state = 1;
    }
  }

  // Return 1 if timer is working (not stopped)
  // and return 0 otherwise
  int working() const { return state; }
};

class window_timer : Graph_lib::Window {
public:
  window_timer(Graph_lib::Point xy, int w, int h, const std::string &title);

private:
  TimerC timerx;
  Button ok;
  Button stop;
  Clock xclock;
  // actions invoked by callbacks
  void timer_go();
  void ok_pressed();
  void stop_pressed();

  // callbacks
  static void cb_timer(Address, Address addr) {
    reference_to<window_timer>(addr).timer_go();
  }
  static void cb_ok(Address, Address addr) {
    reference_to<window_timer>(addr).ok_pressed();
  }
  static void cb_stop(Address, Address addr) {
    reference_to<window_timer>(addr).stop_pressed();
  }
};

int main() {
  using namespace std;

  window_timer win{Point{200, 200}, 600, 400, "Start Stop Moving"};

  return gui_main();
}

window_timer::window_timer(Point xy, int w, int h, const std::string &title)
    : Window(xy, w, h, title), timerx{0.1, cb_timer, 0}, ok{Point{0, 0}, 100,
                                                            50, "Start", cb_ok},
      stop{Point{100, 0}, 100, 50, "Stop", cb_stop}, xclock{Point{200, 200},
                                                            100} {
  attach(xclock);
  attach(timerx);
  attach(ok);
  attach(stop);
}

void window_timer::timer_go() {
  cout << "Clock Tick" << endl;
  for (int i = 0; i != 3; ++i) {
    /* xclock.increase_time(); */
    xclock.refresh();
    redraw();
  }
}

void window_timer::ok_pressed() { timerx.start(); }

void window_timer::stop_pressed() { timerx.stop(); }
