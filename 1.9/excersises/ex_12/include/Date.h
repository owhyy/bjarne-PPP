#ifndef EX_12_DATE_H
#define EX_12_DATE_H

#include <iostream>
#include <vector>

enum class Month {
	jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};
const std::vector<std::string> Month_tbl { "unused",    // burn 0 index
	"January", "February", "March", "April", "May", "June", "July",
	"August", "September", "October", "November", "December"
};

enum class Day {
	sun, mon, tue, wed, thu, fri, sat
};

Month operator++(Month& m);
std::ostream& operator<<(std::ostream& os, const Month& m);

class Z_Date {
public:

private:
	int y=1970;
	Month m = Month::jan;
	int d=1;
};

class Date {
public:
	class Invalid { };              // to throw as exception

	Date(long int);                 // check for valid date and initialize
	Date() : days{0} { }            // default constructor

	// non-modifying operations:
	int day() const;
	Month month() const;
	int year() const;

	// modifying operations (invalidate cache):
	void add_day(int n);
	void add_month(int n);
	void add_year(int n);

	// added to this implementation
	long int get_days() const {
		return days;
	}
	void update_cache() const;				// caches dates

private:
	long int days;

	mutable bool cache_valid = false; // mutable because will change?
	mutable Date_rep cache;						// mutable Z_Date cache?
};

bool is_date(long int);             // true for valid date
bool is_leapyear(int y);            // true if y is a leap year
int days_in_month(int y, Month m);

bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);

std::ostream& operator<<(std::ostream& os, const Date& d);
std::istream& operator>>(std::istream& is, Date& d);
#endif  // EX_12_DATE_H
