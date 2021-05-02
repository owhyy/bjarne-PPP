#ifndef CHAPTER_14_H
#define CHAPTER_14_H

//------------------------------------------------------------------------------

#include "../GUI/Graph.h"
#include "../GUI/ch13.h"
#include <initializer_list>
#include <vector>

//------------------------------------------------------------------------------

struct Smiley : Circle {
  Smiley(Point p, int r);

  void draw_lines() const;

private:
  int r;        // radius
  Circle left;  // left eye
  Circle right; // right eye
  Arc mouth;    // mouth
};

//------------------------------------------------------------------------------

struct Frowny : Circle {
  Frowny(Point p, int r);

  void draw_lines() const;

private:
  int r;        // radius
  Circle left;  // left eye
  Circle right; // right eye
  Arc mouth;    // mouth
};

//------------------------------------------------------------------------------

struct Smiley_hat : Smiley {
  Smiley_hat(Point p, int r);

  void draw_lines() const;

private:
  Rectangle hat;
};

//------------------------------------------------------------------------------

struct Frowny_hat : Frowny {
  Frowny_hat(Point p, int r);

  void draw_lines() const;

private:
  Rectangle hat;
};

//------------------------------------------------------------------------------

struct Immobile_circle : Circle {
  using Circle::Circle;
  void move() = delete;
};

//------------------------------------------------------------------------------

struct Striped_rectangle : Shape {
  Striped_rectangle(Point xy, int ww, int hh);
  Striped_rectangle(Point x, Point y);
  void draw_lines() const;

  int height() const { return h; }
  int width() const { return w; }

private:
  int h; // height
  int w; // width
};

//------------------------------------------------------------------------------

struct Striped_circle : Shape {
  Striped_circle(Point p, int rr);
  void draw_lines() const;

  Point center() const { return point(0); }
  int radius() const { return r; }

private:
  int r;
};

//------------------------------------------------------------------------------

/* struct Striped_closed_polyline : Closed_polyline { */
/*   void draw_lines() const; */
/* }; */

//------------------------------------------------------------------------------

struct Regular_octagon : Closed_polyline {
  Regular_octagon(int rr, Point p);

private:
  int r;
  Point c;
};

//------------------------------------------------------------------------------

struct Group {
  Group() {}
  void move(int dx, int dy);
  void set_color(Color col);
  void set_fill_color(Color col);
  void add(Shape &s);

private:
  Vector_ref<Shape> vr;
};

//------------------------------------------------------------------------------

struct Pseudo_window : Shape {
  Pseudo_window(Point p, int ww, int hh);

  void draw_lines() const;

private:
  int w; // height
  int h; // width
};

//------------------------------------------------------------------------------

struct Binary_tree : Shape {
  Binary_tree(Point p, int ll, string ls);

  void set_node_label(string n, string lbl);
  virtual void draw_lines() const;
  int levels() const { return l; }

protected:
  Vector_ref<Shape> edges;
  Vector_ref<Text> lables;
private:
  int l; // levels
};

//------------------------------------------------------------------------------

struct Binary_tree_square : Binary_tree {
  Binary_tree_square(Point p, int ll, string ls) : Binary_tree(p, ll, ls) {}
  void draw_lines() const;
};

//------------------------------------------------------------------------------

#endif // CHAPTER_14!
