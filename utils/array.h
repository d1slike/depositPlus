#ifndef ARRAY
#define ARRAY
/*Безопасный массив*/
/*В случае выхода за границу, возвращает 0-ой элемент массива*/
template <class T=int, int SIZE = 100> class Array
{
    T array[SIZE];
public:
    T& operator[](register int i)
    {
        if(i >= 0 && i < SIZE)
            return *(array+i);
        return *array;
    }

};

#endif // ARRAY

