#include "money.h"

money::money() {}

money::money(double d) {
	amount_=int((d*100) + 0.5);
}
money::money(std::string cr, double d) {
	currency_ = cr;
	amount_=int((d*100) + 0.5);
}

money::money(int c) : amount_{c} {}
money::money(std::string cr, int c) : amount_{c}, currency_{cr} {}

money money::operator+(const money& rhs) {
	return this->amount() + rhs.amount();
}
money money::operator+(int m) {
	amount_ = amount_ + money{m}.amount();
	return *this;
}
money money::operator-(const money& rhs){
	return this->amount() - rhs.amount();
}
money money::operator-(int m){
	amount_ = amount_ - money{m}.amount();
	return *this;
}
money money::operator*(int m){
	amount_*=m;
	return *this;
}
money money::operator/(int m){
	amount_ /=m;
	return *this;
}
std::ostream& operator<<(std::ostream& os, money m)
{
	return os<<m.currency()<<m.dollars();
}
