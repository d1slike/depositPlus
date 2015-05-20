#pragma once

class Date{
    /*SY - обычный год, LY - високосный*/
    static int DAYS_IN_MOUTH_SY[13] = {-1,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };//Для удобство январь - 1 ячейка
    static int DAYS_IN_MOUTH_LY[13] = {-1,31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

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
    bool isLeapYear();
    int getDaysToNewYear();

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

