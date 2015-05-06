#include "valute.h"
#pragma once

class Money
{
    Valute valute;
    long int value;
public:
    Money(Valute valute, long int value)
    {
        this->valute = valute;
        this->value = value;
    }

    Valute getValute() const
    {
        return valute;
    }

    long int getValue() const
    {
        return value;
    }

    Money& operator=(long int value)
    {
        this->value = value;
        return *this;
    }

    Money& operator+(long int value)
    {
        this->value+=value;
        return *this;
    }

    Money& operator-(long int value)
    {
        this->value-=value;
        return *this;
    }

    Money& operator*(long int value)
    {
        this->value*=value;
        return *this;
    }

    Money& operator/(long int value)
    {
        this->value/=value;
        return *this;
    }

    Money& operator%(long int value)
    {
        this->value%=value;
        return *this;
    }



    //TODO реализовать другие операторы по необходимоти
};

