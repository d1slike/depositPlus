#include "utils/array.h"
#include "utils/section.h"
#include "valute.h"
#include "money.h"
#pragma once

#define R_SIZE 6

class RateSet
{
    m_long start_sum;

public:
    /*Для большей эффективности*/
    Array<int, R_SIZE> section_day;//границы по дням
    Array<double, R_SIZE> base_rates;//номинальные проценты
    Array<double, R_SIZE> effective_rates;//проценты с капитализацией

    RateSet(){}
    RateSet(m_long start_sum, const Array<double, R_SIZE>& base_rates, const Array<double, R_SIZE>& effective_rates, const Array<int, R_SIZE>& section_day)
    {
        this->start_sum = start_sum;
        this->effective_rates = effective_rates;
        this->base_rates = base_rates;
        this->section_day = section_day;
    }

    m_long getSum()
    {
        return start_sum;
    }
};

class RatesMatrix
{
    Array<RateSet, 3> rub_rates;
    Array<RateSet, 3> usd_rates;
    Array<RateSet, 3> eur_rates;

    RateSet& getSuitRates(const Money& m);
public:
    RatesMatrix(){}
    RatesMatrix(Array<RateSet, 3> &rub_rates, Array<RateSet, 3> &usd_rates, Array<RateSet, 3> &eur_rates )
    {
        this->rub_rates = rub_rates;
        this->usd_rates = usd_rates;
        this->eur_rates = eur_rates;
    }
    m_long getStartSum(const Money& m);
    void get(const Money& m, int day, bool withCap, double* rates, int* startDays);
    double get(const Money& m, int day, bool withCap);
};


