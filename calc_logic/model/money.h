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

    bool operator==(long int value)
    {
        return this->value == value;
    }

    bool operator==(const Money& m)
    {
        return value == m.getValue();
    }

    bool operator>(long int value)
    {
        return this->value > value;
    }

    bool operator>(const Money& m)
    {
        return value > m.getValue();
    }

    bool operator>=(long int value)
    {
        return *this > value || *this == value;
    }

    bool operator>=(const Money &m)
    {
        return *this > m || *this == m;
    }

    bool operator<(long int value)
    {
        return !(*this > value);
    }

    bool operator<(const Money &m)
    {
        return !(*this > m);
    }

    bool operator<=(long int value)
    {
        return *this < value || *this == value;
    }

    bool operator<=(const Money &m)
    {
        return *this < m || *this == m;
    }

    //TODO реализовать другие операторы по необходимоти
};

