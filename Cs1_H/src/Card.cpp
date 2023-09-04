#include "../include/Card.hpp"

Card::Card(Rank rank,Suit suit):rank(rank),suit(suit)
{

}

void Card::render()
{
    
}

bool Card::IsBigger(Card card)
{
    return false;
}

Rank Card::GetRank()
{
    return this->rank;
}

Suit Card::GetSuit()
{
    return this->suit;
}

void Card::SetRank(Rank rank)
{
    this->rank = rank;
}

void Card::SetSuit(Suit suit)
{
    this->suit = suit;
}

Card::~Card()
{

}