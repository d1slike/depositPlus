#include "deposit.h"
Money Deposit::calc() // в if добавить ништяков для обработки всего периодов и тд
{
    Money cash=sum;
    cash=0;
    double rates = templ.getRates().get(sum, day_count, capitalize);
    if(capitalize&&!replenishment&&!remove)     //только капитализация
        return cash=calcWithCap(rates,sum.getValue(),day_count).getValue();
    if(!capitalize&&!replenishment&&!remove)    //без всего
        return cash=simpleCalc(rates,sum.getValue(),day_count).getValue();
    if(capitalize&&replenishment&&!remove)//капитализация+добавление
    {
        int d=day_count/30;
        for(int i=0;i<d;i++)
        {
            cash=cash+calcWithCap(rates,sum.getValue()+cash.getValue(),30).getValue();//под вопросом
            sum=sum.getValue()+add_sum.getValue();
        }
        d=day_count%30;
        return cash=cash+calcWithCap(rates,sum.getValue()+cash.getValue(),d).getValue();//под вопросом
    }
    if(!capitalize&&replenishment&&!remove)//без капитализации+добавление
    {
        int d=day_count/30;
        for(int i=0;i<d;i++)
        {
            cash=cash+simpleCalc(rates,sum.getValue(),30).getValue();
            sum=sum.getValue()+add_sum.getValue();
        }
        d=day_count%30;
        return cash=cash+simpleCalc(rates,sum.getValue(),d).getValue();
    }
    if(capitalize&&!replenishment&&remove)      //снятие с капитализацией
    {
        int day_remove=open_date-close_date;
        return cash=calcWithCap(poste_restante,sum.getValue(),day_remove).getValue();
    }
    if(!capitalize&&!replenishment&&remove)     //снятие без капитализации
    {
        int day_remove=open_date-close_date;
        return cash=simpleCalc(poste_restante,sum.getValue(),day_remove).getValue();
    }
    if(capitalize&&replenishment&&remove)//капитализация+добавление+снятие
    {
        int day_remove=open_date-close_date;
        int d=day_remove/30;
        for(int i=0;i<d;i++)
        {
            cash=cash+calcWithCap(poste_restante,sum.getValue()+cash.getValue(),30).getValue();//под вопросом
            sum=sum.getValue()+add_sum.getValue();
        }
        d=day_count%30;
        return cash=cash+calcWithCap(poste_restante,sum.getValue()+cash.getValue(),d).getValue();//под вопросом
    }
    if(!capitalize&&replenishment&&remove)//без капитализации+добавление+снятие
    {
        int day_remove=open_date-close_date;
        int d=day_remove/30;
        for(int i=0;i<d;i++)
        {
            cash=cash+simpleCalc(poste_restante,sum.getValue(),30).getValue();
            sum=sum.getValue()+add_sum.getValue();
        }
        d=day_count%30;
        return cash=cash+simpleCalc(poste_restante,sum.getValue(),d).getValue();
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
            value=value+startsum*pow(persent_coef,D_i)-startsum;
            open_date=open_date+day_to_ny;
            day=day-day_to_ny;
        }
        day_to_ny=open_date.getDaysToNewYear();
        if(day<day_to_ny&&day!=0)
        {
            D_i=day/30.;
            persent_coef=(1.+rates*30./((open_date.isLeapYear()?366.:365.)*100.));
            value=value+startsum*pow(persent_coef,D_i)-startsum;
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
            value=value+startsum*rates*day/((open_date.isLeapYear()?366.:365.)*100.);
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
    return sum >= templ.getRates().getStartSum(sum);
}

bool Deposit::validDate()
{
    return close_date > open_date;
}


