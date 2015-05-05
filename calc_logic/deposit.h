#include "deposittemplate.h"
#include "valute.h"
#include "date.h"

//конкртеный экземпляр вклада
class Deposit
{
    DepositTemplate templ;
    Valute valute;
    int day_count;
    long int start_summ;
public:
    Deposit(const QString& name, Valute v, int day_count, long int start_summ)
    {

    }
};

