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
    /*Deposit(Money sum, int day_count, DepositTemplate templ, Date date)
    {
        this->day_count = day_count;
        this->sum = sum;
        this->templ = templ;
        this->open_date=date;
    }*/
    Money calc();
    Money calcWithCap(double, m_long ,int);
    Money simpleCalc(double, m_long ,int);

    bool validSum(); //сранивает минимальную сумму для открытия вклада из шаблона и текущую сумму
    bool validDate(); //сравнивает минимальное кол-во дней для открытия вклада и текущее положение

    void setTemplate(DepositTemplate& temp)
    {
        templ = temp;
    }

    void setSum(Money& m)
    {
        sum = m;
    }

    void setAddSum(Money &m)
    {
        add_sum = m;
    }

    void setOpenDate(Date& od)
    {
        open_date = od;
    }

    void setCloseDate(Date &cd)
    {
        close_date = cd;
    }

    void setDayCount()
    {
        day_count = open_date - close_date;
    }

    void setDayCount(int i)
    {
        day_count = i;
        close_date = open_date + day_count;
    }

    void setReplenishment(bool b)
    {
        replenishment = b;
    }

    void setCap(bool b)
    {
        capitalize = b;
    }

    void setRemove(bool b)
    {
        remove = b;
    }

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

