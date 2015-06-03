#include "profitresult.h"

ProfitResult::ProfitResult(Date& remove_date, m_long sum, m_long profit)
{
    this->profit = profit;
    this->close_date = remove_date;
    this->sum = sum;
}

QString ProfitResult::toString()
{
    QString s = "Дата закрытия вклада: " + close_date.toString() + "<br>";
    s+= "Сумма на момент закрытия: " + QString::number(sum) + "<br>";
    s+= "Прибыль: "+ QString::number(profit);
    return s;
}

bool ProfitResult::operator >(ProfitResult& tmp)
{
    return profit > tmp.profit;
}

