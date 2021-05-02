#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

struct Iterator {
  virtual double *next() = 0;

protected:
  int pointer;
};
struct Vector_iterator : public Iterator {
  Vector_iterator(const vector<double> &vv) : dv{vv} { pointer = 0; }
  double *next() {
    if (dv.size() > pointer) {
      ++pointer;
      return &dv[pointer - 1];
    } else
      return 0;
  }

private:
  vector<double> dv;
};
struct List_iterator : public Iterator {
  List_iterator(const list<double> &ll) : dl{ll} { pointer = dl.begin(); }
  double *next() {
    double *p;
    if (distance(dl.begin(), pointer) < dl.size()) {
      p = &*pointer;
      ++pointer;
      return p;
    } else
      return 0;
  }

private:
  list<double> dl;
  list<double>::iterator pointer;
};
void print(Iterator &i) {
  double *p;
  p = i.next();
  while (p != 0) {
    cout << *p << ' ';
    p = i.next();
  }
}
int main() {
  vector<double> v{1.3, 12, 919, 93, 9, 193};
  Vector_iterator iv(v);
  print(iv);
}
