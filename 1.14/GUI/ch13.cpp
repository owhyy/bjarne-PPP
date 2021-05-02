#include "ch13.h"

Arc::Arc(Point p, int rr, int ss, int ee) : r{rr}, s{ss}, e{ee} {
  if (s == e)
    error("Bad curve: start and end can't be the same");
  add(Point{p.x - r, p.y - r});
}
void Arc::draw_lines() const {
  if (color().visibility())
    fl_arc(point(0).x, point(0).y, r + r, r + r, s, e);
}

//-------------------------------------------

Box::Box(Point p, int w, int h, int r) {
  sides.add(Point{p.x + r, p.y}, Point{p.x + w - r, p.y});         // top
  sides.add(Point{p.x + r, p.y + h}, Point{p.x + w - r, p.y + h}); // bottom
  sides.add(Point{p.x, p.y + r}, Point{p.x, p.y + h - r});         // left
  sides.add(Point{p.x + w, p.y + r}, Point{p.x + w, p.y + h - r}); // right

 corners.push_back(new Arc{Point{p.x + r, p.y + r}, r, 90, 180});      // tl
  corners.push_back(new Arc{Point{p.x + w - r, p.y + r}, r, 0, 90});    // tr
  corners.push_back(new Arc{Point{p.x + r, p.y + h - r}, r, 180, 270}); // bl
  corners.push_back(
      new Arc{Point{p.x + w - r, p.y + h - r}, r, 270, 360}); // br
}

void Box::draw_lines() const {
  for (int i = 0; i != corners.size(); ++i) {
    corners[i].draw_lines();
  }
  sides.draw_lines();
}

Arrow::Arrow(Point p1, Point p2) {
  add(p1);
  add(p2);
}

void Arrow::draw_lines() const {
  int x_dif = point(1).x - point(0).x;
  int y_dif = point(1).y - point(0).y;
  double angle = atan2(y_dif, x_dif) * 180 / PI;
  double x1 = point(1).x - cos((angle - iso) * PI / 180) * size;
  double y1 = point(1).y - sin((angle - iso) * PI / 180) * size;

  double x2 = point(1).x - cos((angle + iso) * PI / 180) * size;
  double y2 = point(1).y - sin((angle + iso) * PI / 180) * size;

  Polygon Head;
  Head.add(point(1));
  Head.add(Point{int(x1), int(y1)});
  Head.add(Point{int(x2), int(y2)});
  Head.set_color(color());

  Head.draw_lines();   // head
  Shape::draw_lines(); // lines
}

Point n(const Rectangle &r) {
  return Point{r.point(0).x + r.width() / 2, r.point(0).y};
}
Point s(const Rectangle &r) {
  return Point{r.point(0).x + r.width() / 2, r.point(0).y + r.height()};
}
Point w(const Rectangle &r) {
  return Point{r.point(0).x, r.point(0).y + r.height() / 2};
}
Point e(const Rectangle &r) {
  return Point{r.point(0).x + r.width(), r.point(0).y + r.height() / 2};
}
Point nw(const Rectangle &r) { return Point{r.point(0).x, r.point(0).y}; }
Point ne(const Rectangle &r) {
  return Point{r.point(0).x + r.width(), r.point(0).y};
}
Point sw(const Rectangle &r) {
  return Point{r.point(0).x, r.point(0).y + r.height()};
}
Point se(const Rectangle &r) {
  return Point{r.point(0).x + r.width(), r.point(0).y + r.height()};
}
Point center(const Rectangle &r) {
  return Point{r.point(0).x + r.width() / 2, r.point(0).y + r.height() / 2};
}
Point n(const Circle &c) {
  return Point{c.point(0).x + c.radius(), c.point(0).y};
}
Point s(const Circle &c) {
  return Point{c.point(0).x + c.radius(), c.point(0).y + 2 * c.radius()};
}
Point e(const Circle &c) {
  return Point{c.point(0).x + c.radius() * 2, c.point(0).y + c.radius()};
}
Point w(const Circle &c) {
  return Point{c.point(0).x, c.point(0).y + c.radius()};
}
Point center(const Circle &c) {
  return Point{c.point(0).x + c.radius(), c.point(0).y + c.radius()};
}
Point nw(const Circle &c) {
  return Point{c.point(0).x + c.radius() / 3, c.point(0).y + c.radius() / 3};
}
Point ne(const Circle &c) {
  return Point{c.point(0).x + c.radius() * 2 - c.radius() / 3,
               c.point(0).y + c.radius() / 3};
}
Point se(const Circle &c) {
  return Point{c.point(0).x + c.radius() * 2 - c.radius() / 3,
               c.point(0).y + c.radius() * 2 - c.radius() / 3};
}
Point sw(const Circle &c) {
  return Point{c.point(0).x + c.radius() / 3,
               c.point(0).y + 2 * c.radius() - c.radius() / 3};
}
Point n(const Ellipse &e) {
  return Point{e.point(0).x + e.major(), e.point(0).y};
}
Point s(const Ellipse &e) {
  return Point{e.point(0).x + e.major(), e.point(0).y + 2 * e.minor()};
}
Point e(const Ellipse &e) {
  return Point{e.point(0).x + 2 * e.major(), e.point(0).y + e.minor()};
}
Point w(const Ellipse &e) {
  return Point{e.point(0).x, e.point(0).y + e.minor()};
}
Point center(const Ellipse &e) {
  return Point{e.point(0).x + e.major(), e.point(0).y + e.minor()};
}
Point nw(const Ellipse &e) {
  return Point{e.point(0).x + e.major() / 3, e.point(0).y + e.minor() / 3};
}
Point ne(const Ellipse &e) {
  return Point{e.point(0).x + e.major() * 2 - e.major() / 3,
               e.point(0).y + e.minor() / 3};
}
Point se(const Ellipse &e) {
  return Point{e.point(0).x + e.major() * 2 - e.major() / 3,
               e.point(0).y + e.minor() * 2 - e.minor() / 3};
}
Point sw(const Ellipse &e) {
  return Point{e.point(0).x + e.major() / 3,
               e.point(0).y + e.minor() * 2 - e.minor() / 3};
}

Text_box::Text_box(Point p, int ww, int hh, string ss)
    : Rectangle(p, ww, hh), t(Point{p.x + 5, p.y + 16}, ss) {
  add(p);
}
void Text_box::draw_lines() const {
  Rectangle::draw_lines();
  t.draw_lines();
}

Regular_hexagon::Regular_hexagon(Point p, int rr) : c{p}, r{rr} {
  for (int i = 0; i != 360; i += 60) {
    double x = c.x + cos(i * PI / 180) * r;
    double y = c.y + sin(i * PI / 180) * r;
    add(Point{int(x), int(y)});
  }
}
Regular_polygon::Regular_polygon(Point p, int nn, int rr) : c{p}, n{nn}, r{rr} {
  if (n < 3)
    error("Error: polygon can't have less than 2 sides");
  double angle = 360 / n;
  for (double i = 0; i != 360; i += angle) {
    double x = c.x + cos(i * PI / 180) * r;
    double y = c.y + sin(i * PI / 180) * r;
    add(Point{int(x), int(y)});
  }
}

Right_trinagle::Right_trinagle(Point p, int aa, int bb) : a{aa}, b{bb} {
  add(p);
  add(Point{p.x + a, p.y + b});
  add(Point{p.x, p.y + b});
}
Right_trinagle::Right_trinagle(Point p, int aa, int bb, double oo)
    : a{aa}, b{bb}, o{oo}, c{90 - oo} {
  add(p);

  int x = p.x + cos(o * PI / 180) * a;
  int y = p.y - sin(o * PI / 180) * a;
  add(Point{x, y});

  x = p.x - cos(c * PI / 180) * b;
  y = p.y - sin(c * PI / 180) * b;
  add(Point{x, y});
}

Star::Star(Point p, int nn, int rr, int qq) : c{p}, n{nn}, r{rr}, q{qq} {
  double angle = 0;
  double next = 360 / n;

  for (int i = 0; i != n; ++i) {
    int x = c.x + cos(angle * PI / 180) * r;
    int y = c.y + sin(angle * PI / 180) * r;

    add(Point{x, y});

    angle += next * q;
  }
}
