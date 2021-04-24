#include "../excersises/std_lib_facilites.h"

struct Date_9_4_1 {
  int d, m, y;
  void init_day(Date_9_4_1 &date, int dd, int mm, int yy) {
    if (dd > 0 && dd <= 31 && mm > 0 && mm <= 12) {
      date.d = dd;
      date.m = mm;
      date.y = yy;
    } else
      error("Wrong date format\n");
  }
  void add_date(Date_9_4_1 &date, int n) {
    if (date.d == 31 && date.m == 12) {
      date.d = 1;
      date.m = 1;
      date.y++;
    }
    if (date.d == 31 && date.m != 12) {
      date.d = 1;
      ++date.m;
    }
    date.d += n;
  }
};
struct Date_9_4_2 {
  int d, m, y;
  Date_9_4_2(int y, int m, int d) : d{d}, m{m}, y{y} {
    if (d <= 0 || d > 31 || m <= 0 || m > 12)
      error("Wrong date format\n");
  }
  void add_day(Date_9_4_2 &date, int n) {
    if (date.d == 31 && date.m == 12) {
      date.d = 1;
      date.m = 1;
      date.y++;
    }
    if (date.d == 31 && date.m != 12) {
      date.d = 1;
      ++date.m;
    }
    date.d += n;
  }
};
class Date_9_4_3 {
  int y, m, d;

public:
  Date_9_4_3(int y, int m, int d) : d{d}, m{m}, y{y} {
    if (d <= 0 || d > 31 || m <= 0 || m > 12)
      error("Wrong date format\n");
  }
  int month() { return m; }
  int day() { return d; }
  int year() { return y; }
  void add_day(Date_9_4_3 &date, int n) {
    if (date.d == 31 && date.m == 12) {
      date.d = 1;
      date.m = 1;
      date.y++;
    }
    if (date.d == 31 && date.m != 12) {
      date.d = 1;
      ++date.m;
    }
    date.d += n;
  }
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
  dec
};
class Date_9_7_1 {
public:
  Date_9_7_1(int y, Month m, int d) : y{y}, m{m}, d{d} {
    if (m < Month::jan || m > Month::dec || d < 1 && d > 31)
      error("Wrong date format\n");
  }
  int year() { return y; }
  Month month() { return m; }
  int day() { return d; }
  void add_day(Date_9_7_1 &date, int n) {
    if (day() > 31 && month() == Month::dec) {
      date.d = 1;
      date.m = Month::jan;
      date.y++;
    }
    date.d += n;
  }

private:
  int y, d;
  Month m;
};
class Date_9_7_4 {
public:
  Date_9_7_4(int y, Month m, int d) : y{y}, m{m}, d{d} {
    if (m < Month::jan || m > Month::dec || d < 1 && d > 31)
      error("Wrong date format\n");
  }
  int day() const { return d; }
  Month month() const { return m; }
  int year() const { return y; }
  void add_day(int n) { d += n; }

private:
  int y, d;
  Month m;
};

int main() {
  Date_9_4_1 today;
  Date_9_4_1 tommorow = today;
  Date_9_4_2 todayy{1978, 7, 25};
  Date_9_4_2 tommoroww = todayy;
  Date_9_4_3 todayyy{1978, 7, 25};
  Date_9_4_3 tommorowww = todayyy;
  Date_9_7_1 todayyyy{1978, Month::jun, 25};
  Date_9_7_1 tommorowwww = todayyyy;
  Date_9_7_4 todayyyyyy{1978, Month::jun, 25};
  Date_9_7_4 tomorowwwww = todayyyyyy;
  tomorowwwww.add_day(1);
  tommorowwww.add_day(tommorowwww, 1);
  tommorowww.add_day(tommorowww, 1);
  tommoroww.add_day(tommoroww, 1);
  cout<<tomorowwwww.day();
}
