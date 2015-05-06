#include "deposittemplate.h"
#include <map>

class DepositHolder
{
    static std::map<QString, DepositTemplate> all;
public:
    DepositHolder();//TODO реализовать загрузку из dat
    static DepositTemplate getTemplByName(const QString &name){
        if(all.count(name) > 0)
            return all[name];

    }

    ~DepositHolder()
    {
        all.clear();
    }
};

