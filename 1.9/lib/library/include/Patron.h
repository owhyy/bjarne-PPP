#ifndef PATRON_H
#define PATRON_H

#include "std_lib_facilites.h"
class Patron {
public:
  Patron() {}
  Patron(string n, double f);
  Patron(string n);
  string patron_name() const;
  int identity_number() const;
  double fee() const;
  bool has_fee() const;
  void add_fee(double p);

  bool operator==(const Patron &rhs);
  bool operator!=(const Patron &rhs);

private:
  string patron_name_;
  int identity_number_ = rand() % 500 + 1;
  double fee_ = 0.0;
};

ostream &operator<<(ostream &os, const Patron &d);

#endif // PATRON_H
