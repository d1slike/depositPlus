#include "../templates/deposittemplate.h"
#include "valute.h"
#include "date.h"
#include "money.h"

//конкртеный экземпляр вклада
//служит для расчетов
class Deposit
{
    DepositTemplate templ;
    Money sum;
    int day_count;
public:
    Deposit(const Money& sum, int day_count, DepositTemplate templ)
    {
        this->day_count = day_count;
        this->sum = sum;
        this->templ = templ;
    }
};
