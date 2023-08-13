#include <iostream>
#include <stdio.h>

template<typename T>
T* requireNonNull(T *object)
{
    if(!object)
        throw std::invalid_argument("This object can't be null!!!");
    return object;
}

template<typename T>
void shouldBePositive(T val)
{
    if(val <= 0)
        throw std::invalid_argument("This val must be positive");
}