#ifndef DEPOSIT_H
#define DEPOSIT_H

#include "../templates/deposittemplate.h"
#include "valute.h"
#include "date.h"
#include "money.h"
#include "math.h"
#include "profitresult.h"

#define poste_restante 0.01 // ставка вклада до востребования

//конкртеный экземпляр вклада
//служит для расчетов
class Deposit
{
    DepositTemplate templ;
    Money start_sum;
    Money supplement_sum;
    Date open_date;
    Date early_close_date;
    int day_count;
    bool supplementation;//флаг ежемесячного пополнения вклада
    bool capitalization;//флаг капитализации
    bool early_closing;//флаг досрочного снятия

    Money calcWithCap(double, m_long ,int);
    Money simpleCalc(double, m_long ,int);
    Money calc();
public:

    Deposit()
    {
        start_sum = 0;
        supplement_sum = 0;
        open_date = Date();
        early_close_date = Date();
        day_count = 0;
        supplementation = capitalization = early_closing = false;
    }

    ProfitResult getProfit();

    bool validSum(); //сранивает минимальную сумму для открытия вклада из шаблона и текущую сумму
    bool validDate(); //сравнивает минимальное кол-во дней для открытия вклада и текущее положение
    bool validDayCount();
    void setTemplate(DepositTemplate& temp)
    {
        templ = temp;
    }

    void setStartSum(Money& m)
    {
        start_sum = m;
    }

    void setSupplementSum(Money &m)
    {
        supplement_sum = m;
    }

    void setOpenDate(Date& od)
    {
        open_date = od;
    }

    void setEarlyCloseDate(Date &cd)
    {
        early_close_date = cd;
    }

    void setDayCount(int i)
    {
        day_count = i;
    }

    void setSupplementation(bool b)
    {
        supplementation = b;
    }

    void setCapitalisation(bool b)
    {
        capitalization = b;
    }

    void setEarlyClosing(bool b)
    {
        early_closing = b;
    }

    Money& getStartSum()
    {
        return start_sum;
    }

    Money& getSupplementSum()
    {
        return supplement_sum;
    }

    Date getOpenDate()
    {
        return open_date;
    }

    Date getEarlyCloseDate()
    {
        return early_close_date;
    }

    int getDayCount()
    {
        return day_count;
    }

    bool isSupplementation()
    {
        return supplementation;
    }

    bool isCapitalization()
    {
        return capitalization;
    }

    bool isEarlyClosing()
    {
        return early_closing;
    }

    DepositTemplate& getTempl()
    {
        return templ;
    }

    const m_long getCurrentMinSum()
    {
        return templ.getRates().getMinSum(start_sum.getValute());
    }

    const int getCurrentMinDays()
    {
        return templ.getRates().getMinDay(start_sum);
    }

};

#endif

