#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
class rational {
public:
  rational();
  rational(int n, int d);
  rational operator=(const rational &rhs);
  rational operator=(int fraction);

  rational operator+(const rational &rhs);
  rational &operator+=(const rational &rhs);
  rational operator+(int fraction);
  rational &operator+=(int fraction);

  rational operator-(const rational &rhs);
  rational &operator-=(const rational &rhs);
	rational operator-(int fraction);
  rational &operator-=(int fraction);

  rational operator/(const rational &rhs);
  rational &operator/=(const rational &rhs);
	rational operator/(int fraction);
  rational &operator/=(int fraction);

  rational operator*(const rational &rhs);
  rational &operator*=(const rational &rhs);
	rational operator*(int fraction);
  rational &operator*=(int fraction);

  bool operator==(const rational &rhs);
  bool operator!=(const rational &rhs);

  int numerator() const { return this->numerator_; }
  int denominator() const { return this->denominator_; }

  double rational_to_double()const{return 1.0*(numerator_)/denominator_;}

private:
  int numerator_;
  int denominator_;
};
bool is_rational(int d);
std::ostream &operator<<(std::ostream &os, const rational &rhs);
int gcd(int a, int b);

#endif //RATIONAL_H
