#include "date.h"

Date::Date(int _day, int _month, int _year)
{
	day = _day;
	month = _month;
	year = _year;
}

bool Date::operator==(const Date &date)
{
    if (day == date.day && month == date.month && year == date.year)
		return true;
	return false;
}

bool Date::operator>(const Date &date)
{
    if (year > date.year)
		return true;
    else if (year == date.year && month > date.month)
		return true;
    else if (year == date.year && month == date.month && day > date.day)
		return true;

	return false;
}

bool Date::operator<(const Date &date)
{
	return !(*this > date);
}

bool Date::operator<=(const Date &date)
{
    return *this < date || *this == date;
}

bool Date::isLeapYear()
{
    return !(year%4);
}

int Date::getDaysToNewYear()
{

}

bool Date::operator>=(const Date &date)
{
	return *this > date || *this == date;
}

