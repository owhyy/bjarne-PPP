
#include "ch15.h"
#include <algorithm>
using namespace Graph_lib;
int main() {
  ifstream ifs("height-data.txt");
  int height; // temporary storage for height
  int number; // temporary storage for numbers
  vector<int> n_people;
  vector<int> n_heights;
  string xlabel = "height     ";
  while (ifs >> number >> height) {
    n_people.push_back(number);
    n_heights.push_back(height);
    xlabel += to_string(height) + "     ";
  }

  const int y_notches = *max_element(n_people.begin(), n_people.end());
  const int x_notches = n_heights.size();

  constexpr int xmax = 800;
  constexpr int ymax = 600;

  constexpr int xstart = 100;
  constexpr int ystart = ymax / 2 + 250;
  Point axis_start{xstart, ystart};

  constexpr int xlength = xmax - 500;
  constexpr int ylength = ymax - 125;

  const int x_notch_size = xlength / x_notches;
  const int y_notch_size = ylength / y_notches;

  constexpr int x_scale = 2; // only provided for x, as y is ok imo

  Simple_window win(Point{100, 100}, xmax, ymax, "Graph");

  Axis x(Axis::x, axis_start, x_scale * xlength, x_notches, "heights");
  x.label.move(-275, 0); // dunno how to make the labels change accordingly, so
                         // will just leave it at it
  win.attach(x);

  Axis y(Axis::y, axis_start, ylength, y_notches, "number of people");
  win.attach(y);

  Vector_ref<Text> y_labels;
  Vector_ref<Text> x_labels;
  Marked_polyline graph_lines("x");
  for (int i = 0; i != n_people.size(); ++i) {
    graph_lines.add(
        Point{xstart + x_notch_size * x_scale + (x_scale * x_notch_size * i),
              ystart - y_notch_size * n_people[i]});
    y_labels.push_back(
        new Text(Point{xstart - 20, ystart - y_notch_size * n_people[i]},
                 to_string(n_people[i])));

    win.attach(y_labels[y_labels.size() - 1]);
  }
  for (int i = 0; i != n_heights.size(); ++i) {
    x_labels.push_back(
        new Text(Point{xstart + x_notch_size + x_notch_size * x_scale * i + 8,
                       ystart + 15},
                 to_string(n_heights[i]) + "    "));
    win.attach(x_labels[x_labels.size() - 1]);
  }
  win.attach(graph_lines);
  win.wait_for_button();
}
