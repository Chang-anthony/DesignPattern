#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>

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


template<typename T>
std::string ToString(const T& val)
{
    auto convert = [](const T& val)
    {
        std::ostringstream oss;
        oss << val;
        return oss.str();
    };

    return convert(val);
}

template<typename T>
std::string ToString(const std::vector<T>& arr)
{
    auto convert = [](const T& val)
    {
        std::ostringstream oss;
        oss << val;
        return oss.str();
    };
    
    std::string result = "{";
    for(const T& element : arr)
        result += convert(element) + " , ";

    if(!arr.empty())
        result = result.substr(0,result.size() - 3);//移除最後兩個空格與逗號
    result += "]";

    return result;
}
