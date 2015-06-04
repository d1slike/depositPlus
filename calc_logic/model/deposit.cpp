#include "deposit.h"
ProfitResult Deposit::getProfit()
{
    Money profit=calc();
    ProfitResult result(open_date,start_sum.getValue()+profit.getValue(),profit.getValue());
    return result;
}
Money Deposit::calc() // в if добавить ништяков для обработки всего периодов и тд
{
    Money cash=start_sum;
    cash=0;
    double rates =templ.getRates().get(start_sum, day_count, capitalization);
    if(capitalization&&!supplementation&&!early_closing)     //только капитализация
        return cash=calcWithCap(rates,start_sum.getValue(),day_count).getValue();
    if(!capitalization&&!supplementation&&!early_closing)    //без всего
        return cash=simpleCalc(rates,start_sum.getValue(),day_count).getValue();
    if(capitalization&&supplementation&&!early_closing)//капитализация+добавление
    {
        int d=day_count/30;
        for(int i=0;i<d;i++)
        {
            cash=cash+calcWithCap(rates,start_sum.getValue()+cash.getValue(),30).getValue();//под вопросом
            start_sum=start_sum.getValue()+supplement_sum.getValue();
            if(templ.isDynamicRates())
                rates = templ.getRates().get(start_sum, day_count, capitalization);
        }
        d=day_count%30;
        return cash=cash+calcWithCap(rates,start_sum.getValue()+cash.getValue(),d).getValue();//под вопросом
    }
    if(!capitalization&&supplementation&&!early_closing)//без капитализации+добавление
    {
        int d=day_count/30;
        for(int i=0;i<d;i++)
        {
            cash=cash+simpleCalc(rates,start_sum.getValue(),30).getValue();
            start_sum=start_sum.getValue()+supplement_sum.getValue();
            if(templ.isDynamicRates())
                rates = templ.getRates().get(start_sum, day_count, capitalization);
        }
        d=day_count%30;
        return cash=cash+simpleCalc(rates,start_sum.getValue(),d).getValue();
    }
    if(capitalization&&!supplementation&&early_closing)      //снятие с капитализацией
    {
        int day_remove=close_date-open_date;
        return cash=calcWithCap(poste_restante,start_sum.getValue(),day_remove).getValue();
    }
    if(!capitalization&&!supplementation&&early_closing)     //снятие без капитализации
    {
        int day_remove=close_date-open_date;
        return cash=simpleCalc(poste_restante,start_sum.getValue(),day_remove).getValue();
    }
    if(capitalization&&supplementation&&early_closing)//капитализация+добавление+снятие
    {
        int day_remove=close_date-open_date;
        int d=day_remove/30;
        for(int i=0;i<d;i++)
        {
            cash=cash+calcWithCap(poste_restante,start_sum.getValue()+cash.getValue(),30).getValue();//под вопросом
            start_sum=start_sum.getValue()+supplement_sum.getValue();
        }
        d=day_count%30;
        return cash=cash+calcWithCap(poste_restante,start_sum.getValue()+cash.getValue(),d).getValue();//под вопросом
    }
    if(!capitalization&&supplementation&&early_closing)//без капитализации+добавление+снятие
    {
        int day_remove=close_date-open_date;
        int d=day_remove/30;
        for(int i=0;i<d;i++)
        {
            cash=cash+simpleCalc(poste_restante,start_sum.getValue(),30).getValue();
            start_sum=start_sum.getValue()+supplement_sum.getValue();
        }
        d=day_count%30;
        return cash=cash+simpleCalc(poste_restante,start_sum.getValue(),d).getValue();
    }
    return cash;
}

Money Deposit::calcWithCap(double rates, m_long startsum,int day)
{
    m_long value=0;
    int day_to_ny=open_date.getDaysToNewYear();
    double D_i=0,persent_coef;
    while(day)
    {
        day_to_ny=open_date.getDaysToNewYear();
        if(day>=day_to_ny&&day!=0)
        {
            D_i=day_to_ny/30.;
            persent_coef=(1+rates*30./((open_date.isLeapYear()? 366. : 365.)*100.));
            value=(value+startsum)*pow(persent_coef,D_i)-startsum;
            open_date=open_date+day_to_ny;
            day=day-day_to_ny;
        }
        day_to_ny=open_date.getDaysToNewYear();
        if(day<day_to_ny&&day!=0)
        {
            D_i=day/30.;
            persent_coef=(1.+rates*30./((open_date.isLeapYear()?366.:365.)*100.));
            value=(value+startsum)*pow(persent_coef,D_i)-startsum;
            open_date=open_date+day;
            day=0;
        }

    }
    return Money(ABSTRACT, value);
}
Money Deposit::simpleCalc(double rates, m_long  startsum, int day)
{
    m_long value=0;
    int day_to_ny=open_date.getDaysToNewYear();
    while(day)
    {
        day_to_ny=open_date.getDaysToNewYear();
        if(day>=day_to_ny&&day!=0)
        {
            value=value+startsum*rates*day_to_ny/((open_date.isLeapYear()?366.:365.)*100.);
            open_date=open_date+day_to_ny;
            day=day-day_to_ny;
        }
        day_to_ny=open_date.getDaysToNewYear();
        if(day<day_to_ny&&day!=0)
        {
            value=value+startsum*rates*day/((open_date.isLeapYear()?366.:365.)*100.);
            open_date=open_date+day;
            day=0;
        }

    }
    return Money(ABSTRACT, value);
}

bool Deposit::validSum()
{
    return start_sum.getValue() >= templ.getRates().getStartSum(start_sum);
}

bool Deposit::validDate()
{
    return close_date > open_date;
}

bool Deposit::validDayCount()
{
    return day_count >= templ.getRates().getMinimalDay(start_sum);
}


