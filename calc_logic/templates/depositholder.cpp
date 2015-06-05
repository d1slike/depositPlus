#include "depositholder.h"
#include <IO.h>
#include <stdio.h>

using namespace std ;
DepositHolder::DepositHolder()
{
    FILE* file = fopen("data.dat", "r");
    int count=0;
    while(!feof(file))
    {
        QString name;
        char str[10];
        fscanf(file,"%s",str);
        for(int i = 0; i < strlen(str); i++)
                    name[i] = str[i];
        Array<RateSet, 3> rub_rates;
        Array<RateSet, 3> usd_rates;
        Array<RateSet, 3> eur_rates;
        for(int i = 0; i < 3; i++) //
        {
            Array<int, R_SIZE> section_day;//границы по дням
            Array<double, R_SIZE> base_rates;//номинальные проценты
            Array<double, R_SIZE> effective_rates;//проценты с капитализацией
            m_long sum = 0;
            fscanf(file,"%d",&sum);
            for(int j=0;j<6;j++)
                fscanf(file,"%d",&section_day[j]);
            for(int j = 0; j < 6; j++)
            {
                fscanf(file,"%lf%lf",&base_rates[j],&effective_rates[j]);
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
            fscanf(file,"%d",&sum);
            for(int j=0;j<6;j++)
                fscanf(file,"%d",&section_day[j]);
            for(int j = 0; j < 6; j++)
            {
                fscanf(file,"%lf%lf",&base_rates[j],&effective_rates[j]);
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
            fscanf(file,"%d",&sum);
            for(int j=0;j<6;j++)
                fscanf(file,"%d",&section_day[j]);
            for(int j = 0; j < 6; j++)
            {
                fscanf(file,"%lf%lf",&base_rates[j],&effective_rates[j]);
            }
            RateSet tmp(sum, 6, section_day, base_rates, effective_rates);
            eur_rates[i] = tmp;
        }

        RatesMatrix matrix(rub_rates, usd_rates, eur_rates);

        bool can_capitalize=false; //капитализация процентов
        bool can_add=false; //можно добавлять
        bool can_remove=false; //можно досрочно снимать
        bool dynam_rates=false;//градация по ставкам
        int d;
        fscanf(file,"%d",&d);
        if(d)
            can_capitalize=true;
        fscanf(file,"%d",&d);
        if(d)
            can_add=true;
        fscanf(file,"%d",&d);
        if(d)
            can_remove=true;
        fscanf(file,"%d",&d);
        if(d)
            dynam_rates=false;

        DepositTemplate tmp;
        tmp.setName(name);
        tmp.setRates(matrix);
        tmp.setCanCapitalize(can_capitalize);
        tmp.setCanAdd(can_add);
        tmp.setCanRemove(can_remove);
        tmp.setDynamRates(dynam_rates);


        all[count] = tmp;
        names[count] = tmp.getName();
        count++;

}
fclose(file);
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
