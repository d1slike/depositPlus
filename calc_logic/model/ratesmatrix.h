#ifndef RATESMATRIX_H
#define RATESMATRIX_H

#include "utils/array.h"
#include "valute.h"
#include "money.h"


#define R_SIZE 6

class RateSet
{
    m_long start_sum;

public:
    Array<int, R_SIZE> section_day;//границы по дням
    Array<double, R_SIZE> base_rates;//номинальные проценты
    Array<double, R_SIZE> effective_rates;//проценты с капитализацией
    int section_count;
    RateSet(){}
    RateSet(m_long start_sum, int section_count, Array<int, R_SIZE>& section_day, Array<double, R_SIZE>& base_rates, Array<double, R_SIZE>& effective_rates)
    {
        this->start_sum = start_sum;
        this->section_count = section_count;
        this->effective_rates = effective_rates;
        this->base_rates = base_rates;
        this->section_day = section_day;
    }

    m_long getSum()
    {
        return start_sum;
    }

    int getSectionCount()
    {
        return section_count;
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

    int getMinimalDay(Money &m);

    m_long getStartSum(const Money& m);
    void get(const Money& m, int day, bool withCap, double* rates, int* startDays);
    double get(const Money& m, int day, bool withCap);
};

#endif


