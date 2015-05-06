#pragma once

class Date{
    int day;
    int month;
    int year;

public:
    Date(){
        day = -1;
        month = -1;
        year = -1;
    }
    Date(int, int, int);
    bool operator==(const Date &date);
    bool operator>(const Date &date);
    bool operator<(const Date &date);
    bool operator>=(const Date &date);
    bool operator<=(const Date &date);
    //void toString(char*);

    int getDay()
    {
        return day;
    }

    int getMonth()
    {
        return month;
    }

    int getYear()
    {
        return year;
    }

    void setDay(int _day)
    {
        day = _day;
    }

    void setMonth(int  _month)
    {
        month = _month;
    }

    void setYear(int _year)
    {
        year = _year;
    }

};

