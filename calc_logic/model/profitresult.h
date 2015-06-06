#ifndef PROFITRESULT_H
#define PROFITRESULT_H

#include "date.h"
#include "money.h"
#include <QString>
#include <QTableWidgetItem>


struct ProfitResult
{

    QString dep_name;
    QString close_date;
    QString sum;
    QString profit;
    QString rate;

    ProfitResult(){}
    //ProfitResult(Date& close_date, m_long sum, m_long profit);
    ProfitResult(QString& name, Date& close_date,Valute v , m_long sum, m_long profit,double rates_low ,double rates_up);
    //bool operator >(ProfitResult& tmp);
    //QString toString(); //вывод на интерфейс

};

#endif // PROFITRESULT_H
