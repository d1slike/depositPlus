#include <QString>
#include "ratesmatrix.h"


//Шаблон для для депозита
//Шаблоны будут храниться рядом с программой в .dat
class DepositTemplate{
    QString name; //название вклада
    QString info; //описание вклада в <html>
    RatesMatrix rates; //матрица ставок
    bool can_capitalize; //капитализация процентов
    bool can_add; //можно добавлять
    bool can_remove; //можно досрочно снимать

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

    const QString& getName()
    {
        return name;
    }

    const RatesMatrix& getRates()
    {
        return rates;
    }

    const QString& getInfo()
    {
        return info;
    }

};


