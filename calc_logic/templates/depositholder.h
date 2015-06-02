#ifndef DEPOSITHOLDER_H
#define DEPOSITHOLDER_H

#include "deposittemplate.h"
#include <map>

class DepositHolder
{
    std::map<QString, DepositTemplate> all;
public:
    DepositHolder();//TODO реализовать загрузку из dat
    DepositTemplate getTemplByName(const QString &name){
        if(all.count(name) > 0)
            return all[name];

    }

    ~DepositHolder()
    {
        all.clear();
    }
};

#endif



