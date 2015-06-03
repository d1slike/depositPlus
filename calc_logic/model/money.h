#ifndef MONEY_H
#define MONEY_H

#include "valute.h"
#pragma once

typedef unsigned long int m_long; //должно хватить

class Money
{
    Valute valute;
    m_long value;
public:
    Money(){}
    Money(m_long value)
    {
        this->value = value;
    }
    Money(Valute valute, m_long value)
    {
        this->valute = valute;
        this->value = value;
    }
    Valute getValute() const
    {
        return valute;
    }

    m_long getValue() const
    {
        return value;
    }

    void setValute(Valute v)
    {
        valute = v;
    }

    void setValue(m_long v){
        value = v;
    }

    Money& operator=(m_long value)
    {
        this->value = value;
        return *this;
    }

    Money& operator+(m_long value)
    {
        this->value+=value;
        return *this;
    }

    Money& operator-(m_long value)
    {
        this->value-=value;
        return *this;
    }

    Money& operator*(m_long value)
    {
        this->value*=value;
        return *this;
    }

    Money& operator/(m_long value)
    {
        this->value/=value;
        return *this;
    }

    Money& operator%(m_long value)
    {
        this->value%=value;
        return *this;
    }

    bool operator==(m_long value)
    {
        return this->value == value;
    }

    bool operator==(const Money& m)
    {
        return value == m.getValue();
    }

    bool operator>(m_long value)
    {
        return this->value > value;
    }

    bool operator>(const Money& m)
    {
        return value > m.getValue();
    }

    bool operator>=(m_long value)
    {
        return *this > value || *this == value;
    }

    bool operator>=(const Money& m)
    {
        return *this > m || *this == m;
    }

    bool operator<(m_long value)
    {
        return !(*this > value);
    }

    bool operator<(const Money& m)
    {
        return !(*this > m);
    }

    bool operator<=(m_long value)
    {
        return *this < value || *this == value;
    }

    bool operator<=(const Money& m)
    {
        return *this < m || *this == m;
    }

    //TODO реализовать другие операторы по необходимоти
};

#endif
