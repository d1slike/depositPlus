#include "utils/array.h"
#include "valute.h"
#include "money.h"
#pragma once

class Section
{
    long int min;
    long int max;

public:
    Section()
    {
        min = max = -1;
    }

    Section(long int min, long int max)
    {
       this->min = min;
       this->max = max;
    }

    bool contain(long int value)
    {
        return value >=min && value <=max;
    }

    bool operator>=(long int value)
    {
        return value >= min;
    }

    bool operator<=(long int value)
    {
        return value <= max;
    }
};

class RateSet
{
    long int start_sum;
    Array<Section, 6> section_day;//границы по дням
    Array<double, 6> base_rates;//номинальные проценты
    Array<double, 6> effective_rates;//проценты с капитализацией
public:
    RateSet(long int start_sum, const Array<double, 6>& base_rates, const Array<double, 6>& effective_rates, const Array<Section, 6>& section_day)
    {
        this->start_sum = start_sum;
        this->effective_rates = effective_rates;
        this->base_rates = base_rates;
        this->section_day = section_day;
    }

    long int getStartSum()
    {
        return start_sum;
    }

    double get(int day, bool withCap);


};

class RatesMatrix
{
    Array<RateSet, 3> rub_rates;
    Array<RateSet, 3> usd_rates;
    Array<RateSet, 3> eur_rates;

public:
    RatesMatrix(Array<RateSet, 3> &rub_rates)
    {
        this->rub_rates = rub_rates;
        this->usd_rates = usd_rates;
        this->eur_rates = eur_rates;
    }

    const RateSet& operator[](const Money& m);
};


