#ifndef DEPOSITHOLDER_H
#define DEPOSITHOLDER_H

#include "deposittemplate.h"
#include <QStringList>
#include <map>

class DepositHolder
{
    std::map<QString, DepositTemplate> all;
    QStringList list;
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

    QStringList& getNames()
    {
        return list;
    }
};

#endif



