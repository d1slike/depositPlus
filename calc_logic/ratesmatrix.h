#include "utils/array.h"
#include "valute.h"
#pragma once

class Conditions
{
    long int start_sum;
    /*0 - от 91 дня, 1 - от 181, 2 - от 395, 3 - от 546, 4 - от 732, 5 - от 1102*/
    Array<double, 6> base_rates;//номинальные проценты
    Array<double, 6> effective_rates;//проценты с капитализацией
public:
    Conditions(long int start_sum, const Array<double>& base_rates, const Array<double>& effective_rates)
    {
        this->start_sum = start_sum;
        this->effective_rates = effective_rates;
        this->base_rates = base_rates;
    }

    long int getStartSum()
    {
        return start_sum;
    }

    double operator[](int day, bool withCap);


};

class RatesMatrix
{
    Array<Conditions, 3> rub_rates;
    Array<Conditions, 3> usd_rates;
    Array<Conditions, 3> eur_rates;

public:
    RatesMatrix(const Array<Conditions>& rub_rates, const Array<Conditions>& usd_rates, const Array<Conditions>& eur_rates)
    {
        this->rub_rates = rub_rates;
        this->usd_rates = usd_rates;
        this->eur_rates = eur_rates;
    }

    const Conditions& operator[](Valute v, long int sum);//TODO
};


