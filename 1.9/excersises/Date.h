#ifndef DATE_H
#define DATE_H
#include "std_lib_facilites.h"
enum class Day {
  sunday,
  monday,
  tuesday,
  wednesday,
  thursday,
  friday,
  saturday
};

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
  dec,
};

class Date {
public:
  class Invalid {};
  Date();
  Date(int yy, Month mm, int dd);

  int day() const { return d; }
  Month month() const { return m; }
  int year() const { return y; }

  void add_day(int n);
  void add_month(int n);
  void add_year(int n);

private:
  int y;
  Month m;
  int d;
};

bool is_date(int y, Month m, int d);
bool leapyear(int y);

bool operator==(const Date &a, const Date &b);
bool operator!=(const Date &a, const Date &b);

ostream &operator<<(ostream &os, const Date &d);
istream &operator>>(istream &is, Date &dd);

Day day_of_week(const Date &d);
Date next_Sunday(const Date d);
Date next_weekday(const Date &d);
#endif // DATE_H
