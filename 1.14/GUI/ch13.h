#ifndef CHAPTER_13_H
#define CHAPTER_13_H
#include "../GUI/Graph.h"
#include "../GUI/Point.h"
#include "../GUI/Simple_window.h"
#include "../GUI/std_lib_facilities.h"
#include <cmath>

static constexpr double PI = 3.14159265;

struct Arc : Shape {
  Arc() {}
  Arc(Point p, int rr, int ss, int ee);

  int radius() const { return r; }
  int start() const { return s; }
  int end() const { return e; }
  void draw_lines() const;

private:
  int r;
  int s;
  int e;
};
struct Box : Shape {
  Box(Point p, int w, int h, int r);
  void draw_lines() const;

private:
  Lines sides;
  Vector_ref<Arc> corners;
};

struct Arrow : Shape {
  Arrow(Point p1, Point p2);

  void draw_lines() const;
  void set_size(int s) { size = s; }

private:
  int size = 12;
  int iso = 20;
};

Point n(const Rectangle &);
Point s(const Rectangle &);
Point e(const Rectangle &);
Point w(const Rectangle &);
Point center(const Rectangle &);
Point ne(const Rectangle &);
Point se(const Rectangle &);
Point sw(const Rectangle &);
Point nw(const Rectangle &);

Point n(const Circle &);
Point s(const Circle &);
Point e(const Circle &);
Point w(const Circle &);
Point center(const Circle &);
Point ne(const Circle &);
Point se(const Circle &);
Point sw(const Circle &);
Point nw(const Circle &);

Point n(const Ellipse &);
Point s(const Ellipse &);
Point e(const Ellipse &);
Point w(const Ellipse &);
Point center(const Ellipse &);
Point ne(const Ellipse &);
Point se(const Ellipse &);
Point sw(const Ellipse &);
Point nw(const Ellipse &);

struct Text_box : Rectangle {
  Text_box(Point p, int ww, int hh, string ss);

  void draw_lines() const;

private:
  Text t;
};

struct Regular_hexagon : Closed_polyline {
  Regular_hexagon(Point p, int rr);
  Point center() const { return c; }
  int distance_from_center() const { return r; }

private:
  int r;
  Point c;
};
struct Regular_polygon : Closed_polyline {
  Regular_polygon(Point p, int nn, int rr);
  Point center() const { return c; }
  int number_of_sides() const { return n; }
  int distance_from_center() const { return r; }

private:
  Point c;
  int n;
  int r;
};
struct Right_trinagle : Closed_polyline {
  Right_trinagle(Point p, int aa, int bb);
  Right_trinagle(Point p, int aa, int bb, double oo);

private:
  int a;
  int b;
  double o = 0;
  double c = 90;
};

struct Star : Closed_polyline {
  Star(Point p, int nn, int rr, int qq);

private:
  Point c;
  int n;
  int r;
  int q;
};
#endif // !CHAPTER_13_H
