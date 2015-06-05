#ifndef PROFITRESULT_H
#define PROFITRESULT_H

#include "date.h"
#include "money.h"
#include <QString>



class ProfitResult
{
    Date close_date; //дата закрытия вклада, если установлен влаг досрочного закрытия, то устанавливается соответствующая дата
    m_long sum; //сумма в день закрытия вклада
    m_long profit; // прибыль
    double rates_low;// нижний %
    double rates_up;// верхний % по умолчанию 0


public:
    ProfitResult(){}
    ProfitResult(Date& close_date, m_long sum, m_long profit);
    ProfitResult(Date& close_date, m_long sum, m_long profit,double rates_low ,double rates_up);
    bool operator >(ProfitResult& tmp);
    QString toString(); //вывод на интерфейс
};

#endif // PROFITRESULT_H
