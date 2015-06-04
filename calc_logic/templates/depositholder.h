#ifndef DEPOSITHOLDER_H
#define DEPOSITHOLDER_H

#include "deposittemplate.h"
#include <QStringList>
namespace best_rates{
    const static m_long SUM_RUB[3] = {100000,700000,1500000};
    const static m_long SUM_INTER[3] = {3000,20000,50000};
    const static int DAY_COUNT[6]={91,181,395,546,732,1102};
    static const QString NAME_vig="profitable";
    const static double RATES_RUB_vig[36] = {10.50,10.59,10.20,10.42,8.45,8.82,6.50,6.81,6.40,6.81,6.30,6.92,10.80,10.90,10.50,10.73,8.75,9.14,7.45,7.86,7.35,7.89,7.25,8.08,11.00,11.10,10.70,10.94,8.95,9.36,7.60,8.02,7.50,8.07,7.40,8.26};
    const static double RATES_USD_vig[36] = {1.35,1.35,1.75,1.76,2.00,2.02,1.70,1.72,1.60,1.62,1.50,1.53,1.75,1.75,2.50,2.51,2.75,2.79,2.45,2.49,2.35,2.40,2.25,2.33,3.45,3.46,3.90,3.93,4.10,4.19,3.80,3.90,3.65,3.78,3.55,3.74};
    const static double RATES_EUR_vig[36] = {1.25,1.25,1.85,1.86,2.05,2.07,2.05,2.08,1.85,1.88,1.65,1.69,1.55,1.55,2.15,2.16,2.35,2.38,2.35,2.39,2.15,2.20,1.95,2.01,2.10,2.10,2.80,2.82,3.50,3.56,3.50,3.59,3.20,3.30,3.00,3.14};

}

class DepositHolder
{
    Array<DepositTemplate, 10> all;
    Array<QString, 10> names;
    int count;
public:
    DepositHolder();//TODO реализовать загрузку из dat
    DepositTemplate getTempl(int pos){
            return all[pos];
    }

    int getCount()
    {
        return count;
    }

    QString& getName(int pos)
    {
        return names[pos];
    }

};

#endif



