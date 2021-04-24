#include "rational.h"

rational::rational() {
  numerator_ = 0;
	denominator_ = 0;
}
rational::rational(int n, int d) : numerator_{n}, denominator_{d} {
  if (!is_rational(d))
    std::cerr << "Not valid rational";
}

rational rational::operator=(const rational &rhs) {
  denominator_ = rhs.denominator_;
  numerator_ = rhs.numerator_;
  return *this;
}

rational rational::operator=(int fraction)
{
	*this=rational(fraction, fraction);
}

rational rational::operator+(const rational &rhs) {
  rational r;
  if (rhs.denominator_ == denominator_) {
    r.numerator_ = numerator_ + rhs.numerator_;
    r.denominator_ = denominator_;
  } else {
    if (gcd(denominator_, rhs.denominator_) != 1) {
      if (denominator_ > rhs.denominator_) {
        r.denominator_ = denominator_ ;
        r.numerator_ =
            numerator_ + (rhs.numerator_ * denominator_ / rhs.denominator_);
      } else {
        r.denominator_ = rhs.denominator_ ;
        r.numerator_ =
            rhs.numerator_ + (numerator_ * rhs.denominator_ / denominator_);
      }
    } else {
      r.denominator_ = rhs.denominator_ * denominator_;
      r.numerator_ =
          rhs.denominator_ * numerator_ + denominator_ * rhs.numerator_;
    }
  }

  return r;
}
rational rational::operator+(int fraction){
	rational rhs(fraction, fraction);
	rational r;
	if (rhs.denominator_ == denominator_) {
    r.numerator_ = numerator_ + rhs.numerator_;
    r.denominator_ = denominator_;
  } else {
    if (gcd(denominator_, rhs.denominator_) != 1) {
      if (denominator_ > rhs.denominator_) {
        r.denominator_ = denominator_ ;
        r.numerator_ =
            numerator_ + (rhs.numerator_ * denominator_ / rhs.denominator_);
      } else {
        r.denominator_ = rhs.denominator_ ;
        r.numerator_ =
            rhs.numerator_ + (numerator_ * rhs.denominator_ / denominator_);
      }
    } else {
      r.denominator_ = rhs.denominator_ * denominator_;
      r.numerator_ =
          rhs.denominator_ * numerator_ + denominator_ * rhs.numerator_;
    }
  }
  return r;
}
rational &rational::operator+=(const rational &rhs) {
  *this = *this + rhs;
  return *this;
}

rational &rational::operator+=(int fraction) {
	*this = *this + rational(fraction, fraction);
	return *this;
}

rational rational::operator-(const rational &rhs) {
  rational r;
  if (rhs.denominator_ == denominator_) {
    r.numerator_ = numerator_ - rhs.numerator_;
    r.denominator_=denominator_;
  } else {
    if (gcd(denominator_, rhs.denominator_) != 1) {
      if (denominator_ > rhs.denominator_) {
        r.denominator_ = denominator_;
        r.numerator_ =
            numerator_ - rhs.numerator_ * (denominator_ / rhs.denominator_);
      } else {
        r.denominator_ = rhs.denominator_;
        r.numerator_ =
            numerator_ - rhs.denominator_ * (rhs.denominator_ / denominator_);
      }
    } else {
      r.denominator_ = rhs.denominator_ * denominator_;
      r.numerator_ =
          rhs.denominator_ * numerator_ - denominator_ * rhs.numerator_;
    }
  }

  return r;
}

rational rational::operator-(int fraction){
	rational rhs(fraction, fraction);
	rational r;
	if (rhs.denominator_ == denominator_) {
    r.numerator_ = numerator_ - rhs.numerator_;
    r.denominator_=denominator_;
  } else {
    if (gcd(denominator_, rhs.denominator_) != 1) {
      if (denominator_ > rhs.denominator_) {
        r.denominator_ = denominator_;
        r.numerator_ =
            numerator_ - rhs.numerator_ * (denominator_ / rhs.denominator_);
      } else {
        r.denominator_ = rhs.denominator_;
        r.numerator_ =
            numerator_ - rhs.denominator_ * (rhs.denominator_ / denominator_);
      }
    } else {
      r.denominator_ = rhs.denominator_ * denominator_;
      r.numerator_ =
          rhs.denominator_ * numerator_ - denominator_ * rhs.numerator_;
    }
  }

  return r;
}

rational &rational::operator-=(const rational &rhs) {
  *this = *this - rhs;
  return *this;
}

rational &rational::operator-=(int fraction){
	*this = *this - rational(fraction, fraction);
	return *this;
}

rational rational::operator*(const rational &rhs) {
  rational r;
  r.denominator_ = denominator_ * rhs.denominator_;
  r.numerator_ = numerator_ * rhs.numerator_;
  return r;
}

rational rational::operator*(int fraction) {
	rational rhs(fraction, fraction);
	rational r;
	r.denominator_ = denominator_ * rhs.denominator_;
  r.numerator_ = numerator_ * rhs.numerator_;
  return r;
}

rational &rational::operator*=(const rational &rhs) {
  *this = *this * rhs;
  return *this;
}

rational &rational::operator*=(int fraction)
{
	*this = *this * rational(fraction, fraction);
	return *this;
}

rational rational::operator/(const rational &rhs) {
  rational r;
  r.denominator_ = denominator_ * rhs.numerator_;
  r.numerator_ = rhs.denominator_ * numerator_;
  return r;
}

rational rational::operator/(int fraction)
{
	rational rhs(fraction, fraction);
	rational r;
	r.denominator_ = denominator_ * rhs.numerator_;
  r.numerator_ = rhs.denominator_ * numerator_;
  return r;
}

rational &rational::operator/=(const rational &rhs) {
  *this = *this / rhs;
  return *this;
}

rational &rational::operator/=(int fraction){
	*this = *this / rational(fraction, fraction);
	return *this;
}

bool rational::operator==(const rational &rhs) {
  if (denominator_ == rhs.denominator_ && numerator_ == rhs.numerator_)
    return true;
  if (gcd(denominator_, rhs.denominator_ != 1) &&
      gcd(numerator_, rhs.numerator_ != 1))
    return true;
  return false;
}
bool rational::operator!=(const rational &rhs) { return !(*this == rhs); }

bool is_rational(int d) {
  if (d != 0)
    return true;
  return false;
}

std::ostream &operator<<(std::ostream &os, const rational &rhs)
{
	if(rhs.numerator()==0)
		return os<<0;
  os << rhs.numerator() << '/' << rhs.denominator() << '\n';
  return os;
}

int gcd(int a, int b) {
  if (a == 0)
    return b;
  return gcd(b % a, a);
}
