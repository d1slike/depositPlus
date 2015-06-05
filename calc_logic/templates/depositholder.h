#ifndef DEPOSITHOLDER_H
#define DEPOSITHOLDER_H

#include "deposittemplate.h"
#include <QStringList>

class DepositHolder
{
    QList<DepositTemplate> pool;
    int count;

public:
    DepositHolder();
    DepositTemplate getTempl(int pos){
            return pool[pos];
    }

    int getCurCount()
    {
        return count;
    }

    QString getName(int pos)
    {
        return pool[pos].getName();
    }

};

#endif



