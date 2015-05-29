#include "date.h"

using namespace days;

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

bool Date::operator>=(const Date &date)
{
    return *this > date || *this == date;
}

bool Date::isLeapYear()
{
    return !(year%4);
}

Date& Date::operator+(int add_days)
{
    while(add_days)
    {
        if(day == 31 && month == 12)
        {
            day = 1;
            month = 1;
            year++;
        } else if(day == (isLeapYear() ? DAYS_IN_MOUTH_LEAP[month] : DAYS_IN_MOUTH[month]))
        {
            day = 1;
            month++;
        }
        else
            day++;

        add_days--;
    }
    return *this;
}

int Date::getDaysToNewYear()
{
    int days = 0;
    days+=day;
    for(int i = month - 1; i >= 1; i--)
            days+=isLeapYear() ? DAYS_IN_MOUTH_LEAP[i] : DAYS_IN_MOUTH[i];
    return (isLeapYear() ? 366 : 365) - days;
}

