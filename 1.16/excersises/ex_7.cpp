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
  Image airplane;
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

  window_timer win{Point{100, 100}, 600, 400, "Start Stop Moving"};

  return gui_main();
}

window_timer::window_timer(Point xy, int w, int h, const std::string &title)
    : Window(xy, w, h, title), timerx{0.05, cb_timer, 0}, ok{Point{0, 0}, 100,
                                                             50, "Start",
                                                             cb_ok},
      stop{Point{100, 0}, 100, 50, "Stop", cb_stop}, airplane{Point{100, 100},
                                                              "airplane.jpeg"} {
  attach(airplane);
  attach(timerx);
  attach(ok);
  attach(stop);
}

void window_timer::timer_go() {
  cout << "Clock Tick" << endl;
  airplane.move(15, 0);
  if (airplane.point(0).x >= x_max())
    airplane.move(-x_max(), 0);
  redraw();
}

void window_timer::ok_pressed() { timerx.start(); }

void window_timer::stop_pressed() { timerx.stop(); }
