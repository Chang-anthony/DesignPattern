#include "../include/Suit.hpp"

std::map<Suit,std::string> suitToString
{
    {Suit::Club,"1"},
    {Suit::Diamond,"2"},
    {Suit::Heart,"3"},
    {Suit::Spade,"4"}
};

std::map<Suit,std::string> suitToName
{
    {Suit::Club,"Club"},
    {Suit::Diamond,"Diamond"},
    {Suit::Heart,"Heart"},
    {Suit::Spade,"Spade"}
};

std::string SuitToString(Suit suit)
{
    auto it = suitToString.find(suit);
    if(it != suitToString.end())
        return it->second;
    return "0";
}

std::string SuitToName(Suit suit)
{
    auto it = suitToName.find(suit);
    if(it != suitToString.end())
        return it->second;
    return "0";
}