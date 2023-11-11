#include "../include/Number.hpp"

std::map<Number,std::string> numberToString =
{
    {Number::one,"1"},
    {Number::Sec,"2"},
    {Number::Thr,"3"},
    {Number::Four,"4"},
    {Number::Five,"5"},
    {Number::Six,"6"},
    {Number::Seven,"7"},
    {Number::Eight,"8"},
    {Number::Night,"9"},
    {Number::Ten,"10"},
};


std::string NumberToString(Number number)
{
    auto it = numberToString.find(number);
    if(it != numberToString.end())
    {
        return it->second;
    }
    return "0";
}