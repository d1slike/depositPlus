#include "utils/array.h"
#include "valute.h"
#pragma once

class Conditions
{
    long int start_sum;
    /*0 - от 91 дня, 1 - от 181, 2 - от 395, 3 - от 546, 4 - от 732, 5 - от 1102*/
    /*+0 - RUB +1 - USD* +2 - EUR*/
    Array<double, 18> base_rates;//номинальные проценты
    Array<double, 18> effective_rates;//проценты с капитализацией
public:
    Conditions(long int start_sum, const Array<double>& base_rates, const Array<double>& effective_rates)
    {
        this->start_sum = start_sum;
        this->effective_rates = effective_rates;
        this->base_rates = base_rates;
    }

    double getBaseRate(int day, Valute v);
    double getEffectiveRate(int day, Valte v);
    long int getStartSum()
    {
        return start_sum;
    }


};

class RatesMatrix
{
    Array<Conditions, 3> matrix;

public:
    RatesMatrix(const Array<Conditions>& matrix)
    {
        this->matrix = matrix;
    }

    const Conditions& operator[](int i)
    {
        if(i >= 0 && i < 3)
            return matrix[i];
        return matrix[0];
    }
};


