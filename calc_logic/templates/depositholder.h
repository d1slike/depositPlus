#ifndef DEPOSITHOLDER_H
#define DEPOSITHOLDER_H

#include "deposittemplate.h"
#include <QStringList>

class DepositHolder
{
    Array<DepositTemplate, 10> all;
    Array<QString, 10> names;
    int count;
public:
    DepositHolder();//TODO реализовать загрузку из dat
    DepositTemplate getTempl(int pos){
            return all[pos];
    }

    int getCount()
    {
        return count;
    }

    QString& getName(int pos)
    {
        return names[pos];
    }

};

#endif



