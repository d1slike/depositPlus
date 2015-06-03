#include "depositholder.h"
#include <IO.h>
#include <stdio.h>

DepositHolder::DepositHolder()
{
    FILE* file = fopen("data.dat", "wb");
    if(file == NULL)
        return;
    int desk = _fileno(file);
    DepositTemplate *tmp = 0;
    for(unsigned int i = 0; i < _filelength(desk) / sizeof(DepositTemplate); i++)
    {
        fread(tmp, sizeof(DepositTemplate), 1, file);
        all.insert(std::pair<QString, DepositTemplate>(tmp->getName(), *tmp));
        list.append(tmp->getName());
    }
}
