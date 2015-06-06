#include "profitresult.h"

ProfitResult::ProfitResult(QString &name, Date &close_date, Valute v, m_long sum, m_long profit, double rates_low, double rates_up)
{
    this->close_date = close_date.toString();
    this->dep_name = name;
    QString valute = "";
    switch(v)
    {
    case RUB:
        valute.append(" RUB");
        break;
    case USD:
        valute.append(" USD");
        break;
    case EUR:
        valute.append(" EUR");
        break;
    }

    this->sum = QString::number(sum).append(valute);
    this->profit = QString::number(profit).append(valute);
    QString rate("");
    if(rates_low == rates_up)
        rate.append(QString::number(rates_low));
    else if(rates_low < rates_up)
        rate.append(QString::number(rates_low)).append("..").append(QString::number(rates_up));
    else
        rate.append(QString::number(rates_up)).append("..").append(QString::number(rates_low));
    this->rate = rate;

}



