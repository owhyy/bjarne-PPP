#include "Date.h"

// member functions
Date::Date(int y, Month m, int d) : year_{y}, month_{m}, day_{d} {
  if (!is_date(y, m, d))
    error("Invalid date\n");
}
int Date::day() const { return day_; }
int Date::month() const { return int(month_); }
int Date::year() const { return year_; }

// helper functions
Date get_current_date() {
  time_t now = time(0);
  tm *ltm = localtime(&now);
  int y = 1900 + ltm->tm_year;
  int mt = ltm->tm_mon;
  Month m = convert_int_to_month(mt);
  int d = ltm->tm_mday;
  return Date(y, m, d);
}

bool is_date(int y, Month m, int d) {
  if (d <= 0)
    return false;
  if (m < Month::jan || Month::dec < m)
    return false;
  int days_in_month = 31;
  switch (m) {
  case Month::feb:
    days_in_month = (is_leapyear(y)) ? 29 : 28;
    break;
  case Month::apr:
  case Month::jun:
  case Month::sep:
  case Month::nov:
    days_in_month = 30;
    break;
  }
  if (days_in_month < d)
    return false;

  return true;
}

bool is_leapyear(int y) {
  return (y == 2000 || y % 4 == 0 || (y % 100 == 0 && y % 400 == 0));
}

Month convert_int_to_month(const int n) {
  Month m;
  switch (n) {
  case 1:
    m = Month::jan;
    break;
  case 2:
    m = Month::feb;
    break;
  case 3:
    m = Month::mar;
    break;
  case 4:
    m = Month::apr;
    break;
  case 5:
    m = Month::may;
    break;
  case 6:
    m = Month::jun;
    break;
  case 7:
    m = Month::jul;
    break;
  case 8:
    m = Month::aug;
    break;
  case 9:
    m = Month::sep;
    break;
  case 10:
    m = Month::oct;
    break;
  case 11:
    m = Month::nov;
    break;
  case 12:
    m = Month::dec;
    break;
  }
  return m;
}

ostream &operator<<(ostream &os, const Date &d) {
  return os << d.year() << ' ' << d.month() << ' ' << d.day();
}
