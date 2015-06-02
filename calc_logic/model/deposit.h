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
    Date date;
    Date d_remove;
    int day_count;
    bool replenishment;//флаг ежемесячного пополнения вклада
    bool capitalize;//флаг капитализации
    bool remove;//флаг досрочного снятия
public:
    Deposit(Money sum, int day_count, DepositTemplate templ,Date date)
    {
        this->day_count = day_count;
        this->sum = sum;
        this->templ = templ;
        this->date=date;
    }
    Money calc();
    Money calcWithCap(double, m_long ,int);
    Money simpleCalc(double, m_long ,int);
};

#endif

