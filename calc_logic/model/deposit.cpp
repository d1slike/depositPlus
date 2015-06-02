#include "deposit.h"
Money Deposit::calc() // в if добавить ништяков для обработки всего периодов и тд
{
    double rates = templ.getRates().get(sum, day_count, capitalize);
    /*RateSet R;                                      //СДЕЛАЙ ПРОЩЕ ХРЕН ДОСТУЧИШЬСЯ
    RatesMatrix r=templ.getRates();                 //
    R=r[sum];                                       //
    rates=R.get(day_count,templ.isCanCapitalize()); /*/
    if(capitalize)
        return calcWithCap(rates,sum.getValue(),day_count);
    else
        return simpleCalc(rates,sum.getValue(),day_count);
}

Money Deposit::calcWithCap(double rates, m_long startsum,int day)
{
    m_long value=0;
    int day_to_ny=date.getDaysToNewYear();
    double D_i=0,persent_coef;
    while(day)
    {
        day_to_ny=date.getDaysToNewYear();
        if(day>=day_to_ny&&day!=0)
        {
            D_i=day_to_ny/30.;
            persent_coef=(1+rates*30./((date.isLeapYear()? 366. : 365.)*100.));
            value=value+startsum*pow(persent_coef,D_i)-startsum;
            date=date+day_to_ny;
            day=day-day_to_ny;
        }
        day_to_ny=date.getDaysToNewYear();
        if(day<day_to_ny&&day!=0)
        {
            D_i=day/30.;
            persent_coef=(1.+rates*30./((date.isLeapYear()?366.:365.)*100.));
            value=value+startsum*pow(persent_coef,D_i)-startsum;
            date=date+day;
            day=0;
        }

    }
    return Money(ABSTRACT, value);
}
Money Deposit::simpleCalc(double rates, m_long  startsum, int day)
{
    m_long value=0;
    int day_to_ny=date.getDaysToNewYear();
    while(day)
    {
        day_to_ny=date.getDaysToNewYear();
        if(day>=day_to_ny&&day!=0)
        {
            value=value+startsum*rates*day/((date.isLeapYear()?366.:365.)*100.);
            date=date+day_to_ny;
            day=day-day_to_ny;
        }
        day_to_ny=date.getDaysToNewYear();
        if(day<day_to_ny&&day!=0)
        {
            value=value+startsum*rates*day/((date.isLeapYear()?366.:365.)*100.);
            date=date+day;
            day=0;
        }

    }
    return Money(ABSTRACT, value);
}


