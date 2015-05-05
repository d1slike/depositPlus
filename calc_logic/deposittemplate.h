#include <QString>
#include "ratesmatrix.h"


//Шаблон для для депозита
//Шаблоны будут храниться рядом с программой в .dat
class DepositTemplate{
    QString name; //название вклада
    RatesMatrix rates; //матрица ставок


public:
    void setName(const QString &name)
    {
        this->name = name;
    }

    void setRates(const RatesMatrix &rates)
    {
        this->rates = rates;
    }

};


