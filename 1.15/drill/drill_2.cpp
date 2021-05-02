#include "../GUI/Graph.h"
#include "../GUI/Simple_window.h"
#include <algorithm>
#include <iostream>
using namespace Graph_lib;

struct Person {
  Person() = default;
  Person(const string &fn, const string &ln, int a)
      : first_name_{fn}, last_name_{ln}, age_{a} {
    if (!is_person(a, fn, ln))
      error("invalid input");
  }

  string first_name() const { return first_name_; }
  string last_name() const { return last_name_; }
  int age() const { return age_; }
  bool is_person(int a, const string &fn, const string &ln);

  void set_first_name(const string &rhs) { first_name_ = rhs; }
  void set_last_name(const string &rhs) { last_name_ = rhs; }
  void set_age(int rhs) { age_ = rhs; }

private:
  string first_name_;
  string last_name_;
  int age_;
};

istream &operator>>(istream &is, Person &p) {
  Person pp;
  string fn;
  string ln;
  int a;
  cout << "Enter first name: ";
  is >> fn;
  if(isdigit(fn[0]))
    error("invalid first name");
  cout << "Enter last name: ";
  is >> ln;
  if(isdigit(ln[0]))
    error("invalid last name");
  cout << "Enter age: ";
  is >> a;

  pp.set_first_name(fn);
  pp.set_last_name(ln);
  pp.set_age(a);
  if (!pp.is_person(a, fn, ln))
    error("invalid input");
  p = pp;
  return is;
}
ostream &operator<<(ostream &os, Person &p) {
  os << p.first_name() << ' ' << p.last_name() << '\n';
  os << p.age() << '\n';
  return os;
}
bool Person::is_person(int a, const string &fn, const string &ln) {
  if (a <= 0 || a >= 150)
    return false;
  string n = fn + ' ' + ln;
  auto found = find_if(n.begin(), n.end(), [](const char c) {
    return (c == ';' || c == ':' || c == '"' || c == '[' || c == ']' ||
            c == '*' || c == '&' || c == '^' || c == '%' || c == '$' ||
            c == '#' || c == '@' || c == '!');
  });
  if (found != n.end())
    return false;
  else
    return true;
}

int main() {
  /* Simple_window win(Point{100, 100}, 600, 600, "Function Graphics"); */
  vector<Person> people(5);
  for (int i = 0; i != 5; ++i)
    cin >> people[i];
  for (auto i : people)
    cout << i;
}
