#include "profitresult.h"

/*ProfitResult::ProfitResult(Date& remove_date, m_long sum, m_long profit)
{
    this->profit = profit;
    this->close_date = remove_date;
    this->sum = sum;
}*/

ProfitResult::ProfitResult(QString &name, Date &close_date, m_long sum, m_long profit, double rates_low, double rates_up)
{
    this->close_date = QTableWidgetItem(close_date.toString());
    this->dep_name = QTableWidgetItem(name);
    this->sum = QTableWidgetItem(QString::number(sum));
    this->profit = QTableWidgetItem(QString::number(profit));
    this->rate = QTableWidgetItem(QString::number(rates_low));
    /*this->profit = profit;
    this->close_date = close_date;
    this->sum = sum;
    this->rates_low=rates_low;
    if(rates_low!=rates_up)
        this->rates_up=rates_up;
    else
        this->rates_up=0;*/
}

/*QString ProfitResult::toString()
{
    QString s = "Дата закрытия вклада: " + close_date.toString() + "\n";
    s+= "Сумма на момент закрытия: " + QString::number(sum) + "\n";
    s+= "Прибыль: "+ QString::number(profit);
    return s;
}

bool ProfitResult::operator >(ProfitResult& tmp)
{
    return profit > tmp.profit;
}*/

