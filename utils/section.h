/*Класс отрезка для целых чисел*/
#pragma once
class Section
{
    long int min;
    long int max;

public:
    Section()
    {
        min = max = -1;
    }

    Section(long int min, long int max)
    {
       this->min = min;
       this->max = max;
    }

    bool contain(long int value)
    {
        return value >=min && value <=max;
    }

    bool operator>=(long int value)
    {
        return value >= min;
    }

    bool operator<=(long int value)
    {
        return value <= max;
    }
};
