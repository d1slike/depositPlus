#include "../templates/deposittemplate.h"
#include "valute.h"
#include "date.h"
#include "money.h"
#include "math.h"
//конкртеный экземпляр вклада
//служит для расчетов
class Deposit
{
    DepositTemplate templ;
    Money sum;
    Date date;
    int day_count;
    bool capitalize;//установлен ли фалг капи
public:
    Deposit(Money sum, int day_count, DepositTemplate templ,Date date)
    {
        this->day_count = day_count;
        this->sum = sum;
        this->templ = templ;
        this->date=date;
    }
    Money Calc();
    Money CalcCap(double, long int ,int);
    Money CalcNoCap(double, long int ,int);
};

