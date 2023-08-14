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

void lengthshouldBe(std::string str,int min,int max)
{
    if(str.size() > max || str.size() < min)
    {
        std::ostringstream oss;//   透過 ostringstream 來建立一個整數字符串
        oss << str <<" size" << " should be " << min << " ~ " << max << ".";
        throw std::invalid_argument(oss.str());
    }
}

template<typename T>
void valshouldBigger(T val,int min)
{
    if(val < min)
    {
        std::ostringstream oss;//透過 ostringstream 來建立一個整數字符串
        oss << "val " << " should bigger than " << min << ".";
        throw std::invalid_argument(oss.str());
    }
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
