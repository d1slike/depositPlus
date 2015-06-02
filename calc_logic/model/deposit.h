#ifndef DEPOSIT_H
#define DEPOSIT_H

#include "../templates/deposittemplate.h"
#include "valute.h"
#include "date.h"
#include "money.h"
#include "math.h"

#define poste_restante 0.01 // ставка вклада до востребования

//конкртеный экземпляр вклада
//служит для расчетов
class Deposit
{
    DepositTemplate templ;
    Money sum;
    Money add_sum;
    Date open_date;
    Date close_date;
    int day_count;
    bool replenishment;//флаг ежемесячного пополнения вклада
    bool capitalize;//флаг капитализации
    bool remove;//флаг досрочного снятия
public:
    Deposit(Money sum, int day_count, DepositTemplate templ, Date date)
    {
        this->day_count = day_count;
        this->sum = sum;
        this->templ = templ;
        this->open_date=date;
    }
    Money calc();
    Money calcWithCap(double, m_long ,int);
    Money simpleCalc(double, m_long ,int);

    bool validSum(); //сранивает минимальную сумму для открытия вклада из шаблона и текущую сумму
    bool validDate(); //сравнивает минимальное кол-во дней для открытия вклада и текущее положение

    Money& getSum()
    {
        return sum;
    }

    Money& getAddSum()
    {
        return add_sum;
    }

    Date& getOpenDate()
    {
        return open_date;
    }

    Date& getCloseDate()
    {
        return close_date;
    }

    int getDayCount()
    {
        return day_count;
    }

    bool isReplenishment()
    {
        return replenishment;
    }

    bool isCap()
    {
        return capitalize;
    }

    bool isRemove()
    {
        return remove;
    }

    DepositTemplate& getTempl()
    {
        return templ;
    }

};

#endif

