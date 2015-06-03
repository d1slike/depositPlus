#ifndef DATE_H
#define DATE_H

#include <QDate>

namespace days{
    const static int DAYS_IN_MOUTH[13] = {-1,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };//Для удобство январь - 1 ячейка
    const static int DAYS_IN_MOUTH_LEAP[13] = {-1,31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
}

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
    Date (const QDate &);
    int operator-(Date&);//реализация через getDaysToNewYear()
    bool operator==(const Date &date);
    bool operator>(const Date &date);
    bool operator<(const Date &date);
    bool operator>=(const Date &date);
    bool operator<=(const Date &date);
    Date& operator+(int add_days);
    bool isLeapYear();
    int getDaysToNewYear();
    bool checkMe(); //возвращает ИСТИНУ, если дата соотвествтвует корректному формату

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

#endif

