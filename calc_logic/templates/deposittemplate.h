#include <QString>
#include "../model/ratesmatrix.h"


//Шаблон для для депозита
//Шаблоны будут храниться рядом с программой в .dat
class DepositTemplate{
    QString name; //название вклада
    QString info; //описание вклада в <html>
    RatesMatrix rates; //матрица ставок
    bool can_capitalize; //капитализация процентов
    bool can_add; //можно добавлять
    bool can_remove; //можно досрочно снимать
    bool dynam_rates;//градация по ставкам


public:
    void setCanCapitalize(bool can)
    {
        can_capitalize = can;
    }

    void setCanAdd(bool can)
    {
        can_add = can;
    }

    void setCanRemove(bool can)
    {
        can_remove = can;
    }

    void setName(const QString &name)
    {
        this->name = name;
    }

    void setRates(const RatesMatrix &rates)
    {
        this->rates = rates;
    }

    void setInfo(const QString &info)
    {
        this->info = info;
    }

    void setDynamRates(bool dynam_rates)
    {
        this->dynam_rates = dynam_rates;
    }

    bool isCanCapitalize()
    {
        return can_capitalize;
    }

    bool isCanAdd()
    {
       return  can_add;
    }

    bool isCanRemove()
    {
        return can_remove;
    }

    bool isDynamRates()
    {
        return dynam_rates;
    }

    QString& getName()
    {
        return name;
    }

    RatesMatrix& getRates()
    {
        return rates;
    }

    QString& getInfo()
    {
        return info;
    }

};


