#include "deposit.h"
Money Deposit::Calc()// в if добавить ништяков для обработки всего периодов и тд
{
double rates;
rates=templ.getRates()[sum].get(day_count,templ.isCanCapitalize());
if(templ.can_capitalize())
    return CalcCap(rates,sum,day_count);
else
    return CalcNoCap(rates,sum,day_count);
}

Money Deposit::CalcCap(double rates,Money startsum,int day)
{
    Money value=0,persent=1;
    int day_to_ny=date.getDaysToNewYear();
    double D_i=0,persent_coef;
    while(day)
    {
        day_to_ny=date.getDaysToNewYear();
        if(day>=day_to_ny&&day!=0)
        {
            D_i=day_to_ny/30;
            if(date.isLeapYear())
                persent_coef=(1+rates*30/(366*100);
            else
                persent=persent(1+rates*30/(365*100);
            value=value+startsum*pow(persent_coef,D_i)-startsum;
            date=date+day_to_ny;
            day=day-day_to_ny;
        }
        day_to_ny=date.getDaysToNewYear();
        if(day<date.day_to_ny&&day!=0)
        {
            D_i=day/30;
            if(date.isLeapYear())
                persent_coef=(1+rates*30/(366*100);
            else
                persent=persent(1+rates*30/(365*100);
            value=value+startsum*pow(persent_coef,D_i)-startsum;
            date=date+day;
            d=0;
        }

    }
    return value;
}
Money Deposit::CalcNoCap(double rates,Money startsum,int day)
{
    Money value=0;
    int day_to_ny=date.getDaysToNewYear();
    while(day)
    {
        day_to_ny=date.getDaysToNewYear();
        if(day>=day_to_ny&&day!=0)
        {
            if(date.isLeapYear())
                value=value+startsum*rates*day_to_ny/(366*100);
            else
                value=value+startsum*rates*day_to_ny/(365*100);
            date=date+day_to_ny;
            day=day-day_to_ny;
        }
        day_to_ny=date.getDaysToNewYear();
        if(day<date.day_to_ny&&day!=0)
        {
            if(date.isLeapYear())
                value=value+startsum*rates*day/(366*100);
            else
                value=value+startsum*rates*day/(365*100);
            date=date+day;
            day=0;
        }

    }
    return value;
}


