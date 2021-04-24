#include "Date.h"

int main()
{
	Date d(2004, Month::apr,2);
	cout<<next_Sunday(d);

	return 0;
}
