#include "ratesmatrix.h"


double Conditions::operator[](int day, bool isCap)
{
    if(day >=91 && day <= 180)
        return !isCap ? base_rates[0] : effective_rates[0];
    else if(day >= 181 && day <= 394)
        return !isCap ? base_rates[1] : effective_rates[1];
    else if(day >= 395 && day <= 545)
        return !isCap ? base_rates[2] : effective_rates[2];
    else if(day >= 546 && day <= 731)
        return !isCap ? base_rates[3] : effective_rates[3];
    else if(day >= 732 && day <= 1101)
        return !isCap ? base_rates[4] : effective_rates[4];
    else if(day >= 1102)
        return !isCap ? base_rates[5] : effective_rates[5];

    return 0.;

}
