#include "deposittemplate.h"
#include "valute.h"
#include "date.h"
#include "money.h"

//конкртеный экземпляр вклада
class Deposit
{
    DepositTemplate templ;
    Money sum;
    int day_count;
public:
    Deposit(const QString& name, Valute v, int day_count, long int start_summ)
    {

    }
};

