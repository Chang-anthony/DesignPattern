#include <iostream>
#include <stdio.h>

template<typename T>
T* requireNonNull(T* object)
{
    if(!object)
        throw std::invalid_argument("object can't be null.");
    return object;
}
template<typename T>
void shouldBePositive(T val)
{
    if(val <= 0)
        throw std::invalid_argument("val must be positive.");
}
