#include "Patron.h"
// member functions
Patron::Patron(string n, int id, double f) : patron_name_{n}, identity_number_{id}, fee_{f} {}
Patron::Patron(string n, int id) : patron_name_{n}, identity_number_{id} {}
Patron::Patron(string n) : patron_name_{n} {}
string Patron::patron_name() const { return patron_name_; }
int Patron::identity_number() const { return identity_number_; }
double Patron::fee() const { return fee_; }
bool Patron::has_fee() const { return fee_; }
void Patron::add_fee(double p) { this->fee_ += p; };

bool Patron::operator==(const Patron &rhs) {
  return this->patron_name_ == rhs.patron_name_ && this->identity_number_ == rhs.identity_number_;
}
bool Patron::operator!=(const Patron &rhs) {
  return this->patron_name_ != rhs.patron_name_ && this->identity_number_ != rhs.identity_number_;
}

// helper function
ostream &operator<<(ostream &os, const Patron &p) {
  return os << p.patron_name() << ' ' << p.identity_number();
}
