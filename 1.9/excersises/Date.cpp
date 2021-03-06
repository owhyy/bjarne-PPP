#include "Date.h"

Date::Date(int yy, Month mm, int dd) : y{yy}, m{mm}, d{dd} {
  if (!is_date(yy, mm, dd))
    throw Invalid{};
}
const Date &default_date() {
  static Date dd{2001, Month::jan, 1};
  return dd;
}

Date::Date()
    : y{default_date().year()}, m{default_date().month()},
      d{default_date().day()} {}

void Date::add_day(int n) {
  //
}

void Date::add_month(int n) {
  //
}

void Date::add_year(int n) {
  if (m == Month::feb && d == 29 && !leapyear(y + n)) {
    m = Month::mar;
    d = 1;
  }
  y += n;
}

bool is_date(int y, Month m, int d) {
  if (d <= 0)
    return false;
  if (m < Month::jan || Month::dec < m)
    return false;

  int days_in_month = 31;

  switch (m) {
  case Month::feb:
    days_in_month = (leapyear(y)) ? 29 : 28;
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

bool leapyear(int y) {
  //
}
bool operator==(const Date &a, const Date &b) {
  return a.year() == b.year() && a.month() == b.month() && a.day() == b.day();
}

bool operator!=(const Date &a, const Date &b) { return !(a == b); }
ostream &operator<<(ostream &os, const Date &d) {
  return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
}
istream &operator>>(istream &is, Date &dd) {
  int y, m, d;
  char c1, c2, c3, c4;
  is >> c1 >> y >> c2 >> m >> c3 >> d >> c4;
  if (!is)
    return is;
  if (c1 != '(' || c2 != ',' || c3 != ',' || c4 != ')') {
    is.clear(ios_base::failbit);
    return is;
  }
  dd = Date(y, Month(m), d);

  return is;
}

Day day_of_week(const Date &d) {
  //
}
Date next_Sunday(const Date d) {
  //
}
Date next_weekday(const Date &d) {
  //
}
