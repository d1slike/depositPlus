#include "ratesmatrix.h"


void RatesMatrix::get(const Money& m, int day, bool isCap, double *rates, int *startDays)
{
    if(rates == 0 || startDays == 0)
        return;
    RateSet tmp = getSuitRates(m);
    for(int i = 0; i < R_SIZE; i++)
        if(tmp.section_day[i]<=day)
        {
            startDays[i] = tmp.section_day[i];
            rates[i] = isCap ? tmp.effective_rates[i] : tmp.base_rates[i];
        }
}

double RatesMatrix::get(const Money& m, int day, bool isCap)
{
    RateSet tmp = getSuitRates(m);
    for(int i = 5; i >= 0; i++)
        if(tmp.section_day[i] <= day) //TODO проверить
            return isCap ? tmp.effective_rates[i] : tmp.base_rates[i];
    return 0;
}

m_long RatesMatrix::getStartSum(const Money &m)
{
    RateSet tmp = getSuitRates(m);
    return tmp.getSum();
}

RateSet& RatesMatrix::getSuitRates(const Money& m)//TODO обработать минимальные суммы, иначе получим краш
{
    switch(m.getValute())
    {
        case RUB:
                for(int i = 0; i < 3; i++)
                        if(rub_rates[i].getSum() <= m.getValue())
                            return rub_rates[i];
            break;
        case USD:
                for(int i = 0; i < 3; i++)
                        if(usd_rates[i].getSum() <= m.getValue())
                            return usd_rates[i];
            break;
        case EUR:
                for(int i = 0; i < 3; i++)
                        if(eur_rates[i].getSum() <= m.getValue())
                            return eur_rates[i];
            break;


    }

    return rub_rates[0]; //TODO избавиться от этого
}
