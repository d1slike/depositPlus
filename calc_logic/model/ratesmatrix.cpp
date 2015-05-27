#include "ratesmatrix.h"


void RateSet::get(int day, bool isCap, double *rates, Section *sections)
{
    if(rates == 0 || sections == 0)
        return;
    for(int i = 0; i < 6; i++)
        if(section_day[i]<=(day))
        {
            sections[i] = section_day[i];
            rates[i] = isCap ? effective_rates[i] : base_rates[i];
        }
}

double RateSet::get(int day, bool isCap)
{
    for(int i = 0; i < 6; i++)
        if(section_day[i].contain(day))
            return isCap ? effective_rates[i] : base_rates[i];
    return 0;
}

const RateSet& RatesMatrix::operator[](const Money& m)//TODO обработать минимальные суммы, иначе получим краш
{
    switch(m.getValute())
    {
        case RUB:
                for(int i = 0; i < 3; i++)
                        if(rub_rates[i].getStartSum() <= m.getValue())
                            return rub_rates[i];
            break;
        case USD:
                for(int i = 0; i < 3; i++)
                        if(usd_rates[i].getStartSum() <= m.getValue())
                            return usd_rates[i];
            break;
        case EUR:
                for(int i = 0; i < 3; i++)
                        if(eur_rates[i].getStartSum() <= m.getValue())
                            return eur_rates[i];
            break;


    }

    return rub_rates[0]; //TODO избавиться от этого
}
