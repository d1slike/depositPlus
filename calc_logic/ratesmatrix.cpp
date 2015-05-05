#include "ratesmatrix.h"

double Conditions::getBaseRate(int day, Valute v)
{
    if(day >=91 && day <= 180)
        return base_rates[v];
    if(day >= 181 && day <= 394)
        return base_rates[3 + v];
    if(day >= 395 && day <= 545)
        return base_rates[6 + v];
    if(day >= 546 && day <= 731)
        return base_rates[9 + v];
    if(day >= 732 && day <= 1101)
        return base_rates[12 + v];
    if(day >= 1102)
        return base_rates[15 + v];
    return 0.;
}

double Conditions::getEffectiveRate(int day, Valute v)
{
    if(day >=91 && day <= 180)
        return effective_rates[v];
    if(day >= 181 && day <= 394)
        return effective_rates[3 + v];
    if(day >= 395 && day <= 545)
        return effective_rates[6 + v];
    if(day >= 546 && day <= 731)
        return effective_rates[9 + v];
    if(day >= 732 && day <= 1101)
        return effective_rates[12 + v];
    if(day >= 1102)
        return effective_rates[15 + v];
    return 0.;
}
