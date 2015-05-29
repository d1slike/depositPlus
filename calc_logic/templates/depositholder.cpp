#include "depositholder.h"
#include <IO.h>
#include <stdio.h>

DepositHolder::DepositHolder()
{
    FILE* file = fopen("data.dat", "wb");
    if(file == NULL)
        return;
    int desk = fileno(file);
    DepositTemplate *tmp = 0;
    for(in i = 0; i < filelength(desk) / sizeof(DepositTemplate); i++)
    {
        fread(tmp, sizeof(DepositTemplate), 1, file);
        all.insert(tmp->getName(), *tmp);
    }
}
