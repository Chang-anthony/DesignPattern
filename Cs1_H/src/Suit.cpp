#include "../include/Suit.hpp"

std::map<Suit,std::string> suitToString
{
    {Suit::Club,"1"},
    {Suit::Diamond,"2"},
    {Suit::Heart,"3"},
    {Suit::Spade,"4"}
};

std::string SuitToString(Suit suit)
{
    auto it = suitToString.find(suit);
    if(it != suitToString.end())
        return it->second;
    return "0";
}