#include "depositholder.h"
#include <IO.h>
#include <stdio.h>

using namespace std ;

DepositHolder::DepositHolder()
{
    FILE* file = fopen("data.dat", "rb");

    if(file == NULL)
        return;
    int desk = _fileno(file);
    DepositTemplate tmp;
    for(unsigned int i = 1; i < _filelength(desk) / sizeof(DepositTemplate); i++)
    {
        fread(&tmp, sizeof(DepositTemplate), 1, file);
        all[i] = tmp;
        names[i] = tmp.getName();
    }

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
