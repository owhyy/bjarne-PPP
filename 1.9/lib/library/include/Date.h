#ifndef DATE_H
#define DATE_H

#include "std_lib_facilites.h"
enum class Month {
  jan = 1,
  feb,
  mar,
  apr,
  may,
  jun,
  jul,
  aug,
  sep,
  oct,
  nov,
  dec
};
class Date {
public:
  Date(int y, Month m, int d);
  Date() {}
  int day() const;
  int month() const;
  int year() const;

private:
  int year_;
  Month month_;
  int day_;
};

Date get_current_date();
bool is_date(int y, Month m, int d);
bool is_leapyear(int y);
Month convert_int_to_month(const int n);
ostream &operator<<(ostream &os, const Date &d);


#endif // DATE_H
