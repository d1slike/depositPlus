#include "deposit.h"
Money Deposit::Calc() // в if добавить ништяков для обработки всего периодов и тд
{
    double rates = this->templ.getRates().get(sum, day_count, capitalize);
    /*RateSet R;                                      //СДЕЛАЙ ПРОЩЕ ХРЕН ДОСТУЧИШЬСЯ
    RatesMatrix r=templ.getRates();                 //
    R=r[sum];                                       //
    rates=R.get(day_count,templ.isCanCapitalize()); /*/
    if(templ.isCanCapitalize())
        return CalcCap(rates,sum.getValue(),day_count);
    else
        return CalcNoCap(rates,sum.getValue(),day_count);
}

Money Deposit::CalcCap(double rates, long int  startsum,int day)
{
    long int value=0;
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
Money Deposit::CalcNoCap(double rates, long int  startsum, int day)
{
    long int value=0;
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


