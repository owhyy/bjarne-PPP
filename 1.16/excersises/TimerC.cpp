#include "../GUI/GUI.h"
#include "../GUI/Graph.h"
#include "../GUI/Window.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <unistd.h>

using namespace Graph_lib;

inline int rand_int(int min, int max) { // random time?
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);

  return std::uniform_int_distribution<int>{min, max}(generator);
}

class TimerC : public Graph_lib::Widget {
private:
  double time_interval;
  int state; // working = 1, stopped = 0

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

struct Clock : Shape {

  Clock(Point xy, int r)
      : seconds_arm{Point{r, r}, Point{xy.x + r, xy.y + r}},
        minute_arm{Point{r, r}, Point{xy.x + r - 30, xy.y + r - 30}},
        hour_arm{Point{r, r}, Point{xy.x + r - 60, xy.y + r - 60}} {
    Circle{xy, r};
  }
  void refresh();
  void draw_lines() const;

private:
  Line seconds_arm;
  Line minute_arm;
  Line hour_arm;
};

void Clock::draw_lines() const {
  draw_lines();
  seconds_arm.draw();
  minute_arm.draw();
  hour_arm.draw();
}

struct My_window : Graph_lib::Window {
  My_window(Point xy, int w, int h, const string &t);

private:
  // buttons
  Circle c{Point{200, 200}, 100};
  Line arm_1{Point{200, 200}, Point{200, 100}};
  // other objects
  // actions
};

class window_timer : Graph_lib::Window {
public:
  window_timer(Graph_lib::Point xy, int w, int h, const std::string &title);

private:
  TimerC timerx;
  Clock clockx;
  Button ok;
  Button stop;

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

window_timer::window_timer(Graph_lib::Point xy, int w, int h,
                           const std::string &title)
    : Window{xy, w, h, title}, clockx{Point{x_max(), y_max()}, 100},
      timerx{1.0, cb_timer, 1} {
  attach(timerx);
  attach(clockx);
}
void window_timer::timer_go() {
  clockx.refresh();
  redraw();
}
