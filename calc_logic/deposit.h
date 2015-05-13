#include <QString>
#include "date.h"
#ifndef DEPOSIT
#define DEPOSIT



enum Valute{
    RUB,
    DOLLAR,
    EURO
};

class AbstractDeposit{
    QString name;
    Valute valute;
    Date open_date;
    Date close_date;
    int day_count;
    int rate;
public:
    virtual void calcPro0it() = 0;

    const QString& getName()
    {
        return name;
    }

    int getValute()
    {
        return valute;
    }

    const Date& getOpenningDate()
    {
        return open_date;
    }

    const Date& getClosingDate()
    {
        return close_date;
    }

    int getDayCount()
    {
        return day_count;
    }

    int getRate()
    {
        return rate;
    }


};

#endif // DEPOSIT

