#include "Suit.hpp"


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

std::map<std::string, Suit> charTosuit = 
{
    {"C", Suit::Club},
    {"D", Suit::Diamond},
    {"H", Suit::Heart},
    {"S", Suit::Spade}
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

Suit CharToSuit(std::string c)
{
    auto it = charTosuit.find(c);
    if(it != charTosuit.end())
        return it->second;
    
    return Suit::None;
}

int SuitToNumber(Suit suit)
{
    return std::stoi(SuitToString(suit));
}