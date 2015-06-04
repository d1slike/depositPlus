#include "depositholder.h"
#include <IO.h>
#include <stdio.h>

using namespace std ;
using namespace best_rates;
DepositHolder::DepositHolder()
{

        QString name;
        count = 1;
        for(int i = 0; i < 10; i++)
            name[i] = NAME_vig[i];
        Array<RateSet, 3> rub_rates;
        Array<RateSet, 3> usd_rates;
        Array<RateSet, 3> eur_rates;
        for(int i = 0; i < 3; i++) //
        {
            Array<int, R_SIZE> section_day;//границы по дням
            Array<double, R_SIZE> base_rates;//номинальные проценты
            Array<double, R_SIZE> effective_rates;//проценты с капитализацией
            m_long sum = 0;
            sum=SUM_RUB[i];
            for(int j = 0,k=0; j < 6; j++,k+=2)
            {
                section_day[i]=DAY_COUNT[j];
                base_rates[i]=RATES_RUB_vig[i*k];
                effective_rates[i]=RATES_RUB_vig[i*k+1];
            }
            RateSet tmp(sum, 6, section_day, base_rates, effective_rates);
            rub_rates[i] = tmp;
        }
        for(int i = 0; i < 3; i++) //
        {
            Array<int, R_SIZE> section_day;//границы по дням
            Array<double, R_SIZE> base_rates;//номинальные проценты
            Array<double, R_SIZE> effective_rates;//проценты с капитализацией
            m_long sum = 0;
            sum=SUM_INTER[i];
            for(int j = 0,k=0; j < 6; j++,k+=2)
            {
                section_day[i]=DAY_COUNT[j];
                base_rates[i]=RATES_USD_vig[i*k];
                effective_rates[i]=RATES_USD_vig[i*k+1];
            }
            RateSet tmp(sum, 6, section_day, base_rates, effective_rates);
            usd_rates[i] = tmp;
        }
        for(int i = 0; i < 3; i++) //
        {
            Array<int, R_SIZE> section_day;//границы по дням
            Array<double, R_SIZE> base_rates;//номинальные проценты
            Array<double, R_SIZE> effective_rates;//проценты с капитализацией
            m_long sum = 0;
            sum=SUM_INTER[i];
            for(int j = 0,k=0; j < 6; j++,k+=2)
            {
                section_day[i]=DAY_COUNT[j];
                base_rates[i]=RATES_EUR_vig[i*k];
                effective_rates[i]=RATES_EUR_vig[i*k+1];
            }
            RateSet tmp(sum, 6, section_day, base_rates, effective_rates);
            eur_rates[i] = tmp;
        }

        RatesMatrix matrix(rub_rates, usd_rates, eur_rates);

        bool can_capitalize; //капитализация процентов
        bool can_add; //можно добавлять
        bool can_remove; //можно досрочно снимать
        bool dynam_rates;//градация по ставкам
        can_capitalize=true;
        can_add=true;
        can_remove=false;
        dynam_rates=true;

        DepositTemplate tmp;
        tmp.setName(name);
        tmp.setRates(matrix);
        tmp.setCanCapitalize(can_capitalize);
        tmp.setCanAdd(can_add);
        tmp.setCanRemove(can_remove);
        tmp.setDynamRates(dynam_rates);


        all[0] = tmp;
        names[0] = tmp.getName();



    /*ifstream file("data.dat", ios::in | ios::binary);
    if(!file)
        return;
    DepositTemplate *tmp = 0;
    while(file.eof())
    {
        file.
        all.insert(std::pair<QString, DepositTemplate>(tmp->getName(), *tmp));
        list.append(tmp->getName());
    }*/
}
