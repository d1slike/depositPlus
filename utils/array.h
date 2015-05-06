/*Безопасный массив*/
/*В случае выхода за границу, возвращает 0-ой элемент массива*/
#pragma once

template <class T, int SIZE = 100> class Array
{
    T array[SIZE];
public:
    Array(){}
    T& operator[](int i)
    {
        if(i >= 0 && i < SIZE)
            return *(array+i);
        return *array;
    }

};


