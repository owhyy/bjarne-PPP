#include "ch15.h"
#include <FL/fl_draw.H>

//------------------------------------------------------------------------------

Func::Func(Fct f, double r1, double r2, Point orig, int cnt, double xsc,
           double ysc, double p)
    : fc{f}, r_min_{r1}, r_max_{r2}, origin_{orig}, count_{cnt}, xscale_{xsc},
      yscale_{ysc}, precision_{p} {
  if (r2 - r1 <= 0)
    error("bad graphing range");
  if (cnt <= 0)
    error("non-positive graphing count");
  double dist = (r2 - r1) / cnt;
  double r = r1;
  for (int i = 0; i < cnt; ++i) {
    add(Point{orig.x + int(r * xsc), orig.y - int(f(r) * ysc)});
    r += dist;
  }
}

//------------------------------------------------------------------------------

Func::Func(double (*f)(double), double r1, double r2, Point orig, int cnt,
           double xsc, double ysc, double p)
    : Func{static_cast<Fct>(f), r1, r2, orig, cnt, xsc, ysc} {}

//------------------------------------------------------------------------------

void Func::reset() { // deletes points and resets members
  clear_points();
  fc = nullptr;
  r_min_ = 0;
  r_max_ = 0;
  origin_ = Point{0, 0};
  count_ = 100;
  xscale_ = 25;
  yscale_ = 25;
  precision_ = 1.0;
}

//------------------------------------------------------------------------------

void Func::call_function() { // draws function again
  if (r_max_ - r_min_ <= 0)
    error("bad graphing range");
  if (count_ <= 0)
    error("non-positive graphing count");
  double dist = (r_max_ - r_min_) / count_;
  double r = r_min_;
  for (int i = 0; i < count_; ++i) {
    add(Point{origin_.x + int(r * xscale_), origin_.y - int(fc(r) * yscale_)});
    r += dist;
  }
}

//------------------------------------------------------------------------------

Bar_graph::Bar_graph(Point xy, double w, double sp, double ys)
    : width_{w}, space_{sp}, y_scale_{ys} {
  add(xy);
}
//------------------------------------------------------------------------------

void Bar_graph::draw_lines() const {

  for (int i = 0; i != data_.size(); ++i) {
    labels_[i].draw();
    int x = point(0).x + i * (width_ + space_) + space_ / 2;
    int y = point(0).y - (data_[i] > 0 ? data_[i] * y_scale_ : 0);

    if (fill_color().visibility()) {
      fl_color(fill_color().as_int());
      fl_rectf(x, y, width_, ceil(abs(data_[i] * y_scale_)));
      fl_color(color().as_int());
    }

    if (color().visibility()) {
      fl_color(color().as_int());
      fl_rect(x, y, width_, ceil(abs(data_[i] * y_scale_)));
    }
  }
}

//------------------------------------------------------------------------------

void Bar_graph::add_value(double d) {
  data_.push_back(d);
  int x = point(0).x + data_.size() - 1 * (width_ + space_) + space_ / 2;
  int y = point(0).y - d * y_scale_;
  if (d < 0)
    y += 30;
  else
    y -= 20;

  labels_.push_back(new Text{Point{x, y}, ""});
}

//------------------------------------------------------------------------------
