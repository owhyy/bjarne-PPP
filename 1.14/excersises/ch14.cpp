#include "ch14.h"
#include <FL/Enumerations.H>
#include <FL/fl_draw.H>
#include <algorithm>
#include <initializer_list>
#include <sstream>

//------------------------------------------------------------------------------

Smiley::Smiley(Point p, int r)
    : Circle{p, r}, left{Point{p.x - r / 3, p.y - r / 3}, r / 4},
      right{Point{p.x + r / 3, p.y - r / 3}, r / 4}, mouth{p, r * 2 / 3, 200,
                                                           340} {}

//------------------------------------------------------------------------------

void Smiley::draw_lines() const {
  Circle::draw_lines();
  left.draw_lines();
  right.draw_lines();
  mouth.draw_lines();
}

//------------------------------------------------------------------------------

Frowny::Frowny(Point p, int r)
    : Circle{p, r}, left{Point{p.x - r / 3, p.y - r / 3}, r / 4},
      right{Point{p.x + r / 3, p.y - r / 3}, r / 4},
      mouth{Point{p.x, p.y + r * 3 / 4}, r * 2 / 3, 22, 157} {}

//------------------------------------------------------------------------------

void Frowny::draw_lines() const {
  Circle::draw_lines();
  left.draw_lines();
  right.draw_lines();
  mouth.draw_lines();
}

//------------------------------------------------------------------------------

Smiley_hat::Smiley_hat(Point p, int r)
    : Smiley{p, r}, hat{Point{p.x - r * 3 / 4, p.y - r * 5 / 4}, r * 3 / 2,
                        r / 2} {
  hat.set_fill_color(Color::blue);
}

//------------------------------------------------------------------------------

void Smiley_hat::draw_lines() const {
  Smiley::draw_lines();
  hat.draw_lines();
}

//------------------------------------------------------------------------------

Frowny_hat::Frowny_hat(Point p, int r)
    : Frowny{p, r}, hat{Point{p.x - r * 3 / 4, p.y - r * 5 / 4}, r * 3 / 2,
                        r / 2} {

  hat.set_fill_color(Color::red);
}

//------------------------------------------------------------------------------

void Frowny_hat::draw_lines() const {
  Frowny::draw_lines();
  hat.draw_lines();
}

//------------------------------------------------------------------------------

Striped_rectangle::Striped_rectangle(Point xy, int ww, int hh) : w(ww), h(hh) {
  if (h <= 0 || w <= 0)
    error("Bad rectangle: non-positive side");
  add(xy);
}

//------------------------------------------------------------------------------

Striped_rectangle::Striped_rectangle(Point x, Point y)
    : w{y.x - x.x}, h{y.y - x.y} {
  if (h <= 0 || w <= 0)
    error("Bad rectangle: non-positive side");
  add(x);
}

//------------------------------------------------------------------------------

void Striped_rectangle::draw_lines() const {

  if (fill_color().visibility()) { // fill
    fl_color(fill_color().as_int());
    for (int i = point(0).y + 2; i != point(0).y + h; i += 2)
      fl_line(point(0).x, i, point(0).x + w - 1, i);
    fl_color(color().as_int()); // reset color
  }
  if (color().visibility()) {
    fl_color(color().as_int());
    fl_rect(point(0).x, point(0).y, w, h);
  }
}

//------------------------------------------------------------------------------

Striped_circle::Striped_circle(Point p, int rr) : r{rr} { add(p); }

//------------------------------------------------------------------------------

void Striped_circle::draw_lines() const {

  if (fill_color().visibility()) {
    fl_color(fill_color().as_int());
    for (int i = point(0).y + 2 - r; i != point(0).y + r; i += 2) {
      int x_mod = sqrt(pow(r, 2) - pow(point(0).y - i, 2));
      fl_line(point(0).x - x_mod, i, point(0).x + x_mod, i);
    }
    fl_color(color().as_int());
  }
  if (color().visibility()) {
    fl_color(color().as_int());
    fl_arc(point(0).x - r, point(0).y - r, r + r, r + r, 0, 360);
  }
}

//------------------------------------------------------------------------------

inline pair<double, double> line_intersect(Point p1, Point p2, Point p3,
                                           Point p4, bool &parallel) {
  double x1 = p1.x;
  double x2 = p2.x;
  double x3 = p3.x;
  double x4 = p4.x;
  double y1 = p1.y;
  double y2 = p2.y;
  double y3 = p3.y;
  double y4 = p4.y;

  double denom = ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
  if (denom == 0) {
    parallel = true;
    return pair<double, double>(0, 0);
  }
  parallel = false;
  return pair<double, double>(
      ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denom,
      ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denom);
}

//------------------------------------------------------------------------------

bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4,
                            Point &intersection) {
  bool parallel;
  pair<double, double> u = line_intersect(p1, p2, p3, p4, parallel);
  if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1)
    return false;
  intersection.x = p1.x + u.first * (p2.x - p1.x);
  intersection.y = p1.y + u.first * (p2.y - p1.y);
  return true;
}

//------------------------------------------------------------------------------
/* void Striped_closed_polyline::draw_lines() const { */
/*   if (number_of_points() > 1) */
/*     if (fill_color().visibility()) { */
/*       fl_color(fill_color().as_int()); */

/*       int x_min = point(0).x; */
/*       int x_max = point(0).x; */
/*       int y_min = point(0).y; */
/*       int y_max = point(0).y; */

/*       for (int i = 0; i != number_of_points(); ++i) { */
/*         if (point(i).x > x_max) */
/*           x_max = point(i).x; */
/*         if (point(i).x < x_min) */
/*           x_min = point(i).x; */
/*         if (point(i).y > y_max) */
/*           y_max = point(i).y; */
/*         if (point(i).y < y_min) */
/*           y_min = point(i).y; */
/*       } */

/*       // box around polygon with 5px in x direction */
/*       x_min -= 5; */
/*       x_max += 5; */

/*       for (int y = y_min; y != y_max; y += 2) { */
/*         vector<Point> intersections; // vector of intersections */
/*         Point intersec;              // point of intersection */
/*         for (int i = 1; i != number_of_points(); ++i) { */
/*           if (line_segment_intersect(Point{x_min, y}, Point{x_max, y},
 * point(i), */
/*                                      point(i - 1), */
/*                                      intersec)) // if there is a interection
 */
/*             intersections.push_back(intersec); // add to vector of
 * intersections */
/*         } */
/*         // add closing line */
/*         if (line_segment_intersect(Point{x_min, y}, Point{x_max, y}, */
/*                                    point(number_of_points() - 1), point(0),
 */
/*                                    intersec)) */
/*           intersections.push_back(intersec); */

/*         sort(intersections.begin(), intersections.end(), // sort by x */
/*              [](const Point &p1, const Point &p2) { return p1.x < p2.x; });
 */

/*         // draw line between every 2nd pair of points */
/*         for (int i = 0; i != intersections.size(); i += 2) */
/*           fl_line(intersections[i - 1].x, intersections[i - 1].y, */
/*                   intersections[i].x, intersections[i].y); */
/*       } */
/*       fl_color(color().as_int()); // reset color */
/*     } */

/*   if (color().visibility()) { */
/*     Shape::draw_lines(); */
/*     // draw closing line */
/*     fl_line(point(number_of_points() - 1).x, point(number_of_points()).y, */
/*             point(0).x, point(0).y); */
/*   } */
/* } */

//------------------------------------------------------------------------------

Regular_octagon::Regular_octagon(int rr, Point p) : r{rr}, c{p} {
  for (int i = 0; i != 360; i += 45) {
    double x = c.x + cos(i * PI / 180) * r;
    double y = c.y + sin(i * PI / 180) * r;
    add(Point{int(x), int(y)});
  }
}

//------------------------------------------------------------------------------

void Group::move(int dx, int dy) {
  for (int i = 0; i != vr.size(); ++i)
    vr[i].move(dx, dy);
}

//------------------------------------------------------------------------------

void Group::set_color(Color col) {
  for (int i = 0; i != vr.size(); ++i)
    vr[i].set_color(col);
}

//------------------------------------------------------------------------------

void Group::set_fill_color(Color col) {
  for (int i = 0; i != vr.size(); ++i)
    vr[i].set_fill_color(col);
}

//------------------------------------------------------------------------------

void Group::add(Shape &s) { vr.push_back(s); }

//------------------------------------------------------------------------------

Pseudo_window::Pseudo_window(Point p, int ww, int hh) : w{ww}, h{hh} { add(p); }

//------------------------------------------------------------------------------

void Pseudo_window::draw_lines() const {
  Box win(point(0), w, h, 5);
  win.set_fill_color(Color::white);
  Text_box button(Point{point(0).x + w - 50, point(0).y}, 50, 20, "Next");
  Rectangle title_bar(Point{point(0).x, point(0).y - 20}, w + 1, 25);
  Rectangle shape(Point{point(0).x + w / 2, point(0).y + h / 2}, w / 3, h / 3);
  shape.set_fill_color(Color::blue);
  title_bar.set_fill_color(Color::black);
  title_bar.draw_lines();
  shape.draw_lines();
  win.draw_lines();
  button.draw_lines();
}

//------------------------------------------------------------------------------

Binary_tree::Binary_tree(Point p, int ll, string ls) : l{ll} {

  if (l < 0)
    error("Error: tree must have at least 1 node");
  if (l == 0)
    return;
  add(p);

  int dx = 35;
  int dy = 100;

  for (int i = 2; i <= l; ++i) {
    for (int j = 0; j != pow(2, i - 1); ++j) {
      int x = p.x - ((pow(2, i - 1) - 1) / 2 - j) * pow(2, l - i) * dx;
      int y = p.y + (i - 1) * dy;
      add(Point{x, y});
    }
  }
  for (int i = 0; i != number_of_points() / 2; ++i) {
    if (ls == "ad") {
      edges.push_back(new Arrow(
          point(i), Point{point(2 * i + 1).x, point(2 * i + 1).y - 12}));
      edges.push_back(new Arrow(
          point(i), Point{point(2 * i + 2).x, point(2 * i + 2).y - 12}));
    } else if (ls == "au") {
      edges.push_back(
          new Arrow(point(2 * i + 1), Point{point(i).x, point(i).y + 12}));
      edges.push_back(
          new Arrow(point(2 * i + 2), Point{point(i).x, point(i).y + 12}));
    } else {
      edges.push_back(new Line(point(i), point(2 * i + 1)));
      edges.push_back(new Line(point(i), point(2 * i + 2)));
    }
  }
  for (int i = 0; i != number_of_points(); ++i)
    lables.push_back(new Text(Point{point(i).x + 13, point(i).y - 13}, ""));
}

//------------------------------------------------------------------------------

void Binary_tree::set_node_label(string n, string lbl) {
  if (n.size() < 1 || n.size() > l)
    error("Error: set_label invalid node");
  istringstream iss(n);
  char ch;
  iss.get(ch);
  if (n.size() == 1)
    switch (ch) {
    case 'l':
    case 'r':
      lables[0].set_label(lbl);
      break;
    default:
      error("Error: set_label invalid node char");
    }

  int ind = 0;
  while (iss.get(ch)) {
    switch (ch) {
    case 'l':
      ind = 2 * ind + 1;
      break;
    case 'r':
      ind = 2 * ind + 2;
      break;
    default:
      error("Error: set_label invalid node char");
    }
  }
  lables[ind].set_label(lbl);
}

//------------------------------------------------------------------------------

void Binary_tree::draw_lines() const {
  if (color().visibility()) {
    for (int i = 0; i != edges.size(); ++i)
      edges[i].draw();

    for (int i = 0; i != number_of_points(); ++i)
      lables[i].draw();

    const int r = 12;
    fl_color(fl_rgb_color(192, 192, 192));
    for (int i = 0; i != number_of_points(); ++i)
      fl_pie(point(i).x - r, point(i).y - r, r + r - 1, r + r - 1, 0, 360);
    fl_color(color().as_int());
    for (int i = 0; i != number_of_points(); ++i)
      fl_arc(point(i).x - r, point(i).y - r, r + r, r + r, 0, 360);
  }
}

//------------------------------------------------------------------------------

void Binary_tree_square::draw_lines() const {
  if (color().visibility()) {
    for (int i = 0; i != edges.size(); ++i)
      edges[i].draw();

    for (int i = 0; i != number_of_points(); ++i)
      lables[i].draw();

    const int r = 12;
    fl_color(fl_rgb_color(192, 192, 192));
    for (int i = 0; i != number_of_points(); ++i)
      fl_rectf(point(i).x - r, point(i).y - r, r + r, r + r);
    fl_color(color().as_int());
    for (int i = 0; i != number_of_points(); ++i)
      fl_rect(point(i).x - r, point(i).y - r, r + r, r + r);
  }
}

//------------------------------------------------------------------------------
