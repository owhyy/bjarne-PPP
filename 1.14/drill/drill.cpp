#include <iostream>
#include <string>
using namespace std;

class B1 {
public:
  virtual void vf() { cout << "B1::vf()\n"; }
  void f() { cout << "B1::f()\n"; }
};

class D1 : public B1 {
public:
  void vf() { cout << "D1::vf()\n"; }
  void f() { cout << "D1::f()\n"; }
  virtual void pvf() = 0;
};

class D2 : public D1 {
public:
  void pvf() { cout << "D2::pvf()\n"; }
};

class B2 {
public:
  virtual void pvf() = 0;
};

class D21 : public B2 {
public:
  void pvf() { cout << s << '\n'; }
  string s;
};

class D22 : public D21 {
  public:
  void f(B2& b2){b2.pvf();}
  int n;
};

int main() {
  B1 b1;
  b1.vf();
  b1.f();

  cout << '\n';

  /* D1 d1; */
  /* d1.vf(); */
  /* d1.f(); */

  cout << '\n';

  /* B1 &b1r(d1); */
  /* b1r.vf(); */
  /* b1r.f(); */

  D2 d2;
  d2.vf();
  d2.f();
  d2.pvf();

  cout << '\n';

  D21 d21;
  d21.s = "YEAH";
  d21.pvf();
  
  cout << '\n';

  D22 d22;
  d22.f(d21);
}
