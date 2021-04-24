#ifndef MONEY_H
#define MONEY_H

#include <iostream>
#include <string>
class money
{
	public:
		money();
		money(int c);
		money(double d);
		money(std::string currency, double d);
		money(std::string currency, int c);
		int amount()const{return amount_;}
		std::string currency()const{return currency_;}
		money operator+(const money& rhs);
		money operator+(int m);
		money operator-(const money& rhs);
		money operator-(int m);
		money operator*(int m);
		money operator/(int m);
		double dollars()const{return double(amount_)/100;}
	private:
		std::string currency_ = "$";
		long int amount_;
};
	std::ostream& operator<<(std::ostream& os, money m);



#endif // MONEY_H
