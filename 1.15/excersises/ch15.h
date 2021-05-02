#include "../GUI/Graph.h"
#include "../GUI/Simple_window.h"
#include <algorithm>

typedef std::function<double(double)> Fct;

//------------------------------------------------------------------------------

struct Func : Shape {
  Func(Fct f, double r1, double r2, Point orig, int cnt = 100, double xsc = 25,
       double ysc = 25, double p = 1.0);
  Func(double (*f)(double), double r1, double r2, Point orig, int cnt = 100,
       double xsc = 25, double ysc = 25, double p = 1.0);

  void reset();
  void call_function();

  // getters. not sure if needed, can be uncommented
  /* Fct used_function() const { return fc; } */
  /* double range_min() const { return r_min_; } */
  /* double range_max() const { return r_max_; } */
  /* Point origin() const { return origin_; } */
  /* int count() const { return count_; } */
  /* double xscale() const { return xscale_; } */
  /* double yscale() const { return yscale_; } */

  void set_function(Fct ff) { fc = ff; }
  void set_range(double rmi, double rma) {
    r_min_ = rmi;
    r_max_ = rma;
  }
  void set_origin(int ox, int oy) { origin_ = Point{ox, oy}; }
  void set_count(int c) { count_ = c; }
  void set_scaling(double xs, double ys) { xscale_ = xs, yscale_ = ys; }
  void set_precision(double p) { precision_ = p; }

private:
  Fct fc;            // function
  double r_min_;     // beginning of range
  double r_max_;     // end of range
  Point origin_;     // origin
  int count_;        // number of repertitions
  double xscale_;    // scaling of x
  double yscale_;    // scaling of y
  double precision_; // precision (why?)
};

//------------------------------------------------------------------------------

struct Bar_graph : Shape {
  Bar_graph(Point xy, double w = 10, double sp = 50, double ys = 25);
  void draw_lines() const;
  void add_value(double d);
  void set_label(const string& l, int n) {labels_[n].set_label(l);}
private:
  vector<double> data_;    // data
  Vector_ref<Text> labels_; // labels
  double width_;           // width of bar
  double space_;           // space between bars
  double y_scale_;         // height of bar
};
