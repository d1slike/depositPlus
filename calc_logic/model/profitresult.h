#ifndef PROFITRESULT_H
#define PROFITRESULT_H

#include "date.h"
#include "money.h"
#include <QString>



class ProfitResult
{
    Date remove_date; //дата закрытия вклада, если установлен влаг досрочного закрытия, то устанавливается соответствующая дата
    m_long sum; //сумма в день закрытия вклада
    m_long profit; // прибыль


public:
    ProfitResult(){}
    ProfitResult(Date& remove_date, m_long sum, m_long profit);
    bool operator >(ProfitResult& tmp);
    QString toString(); //вывод на интерфейс
};

#endif // PROFITRESULT_H
