#include "Card.hpp"
#include "Deck.hpp"


Card::Card(Rank rank,Suit suit):rank(rank),suit(suit),deck(nullptr)
{
    
}

Card::Card(Rank rank,Suit suit,Deck* deck):rank(rank),suit(suit),deck(deck)
{

}

void Card::render()
{
    std::cout << SuitToName(this->GetSuit())[0]  
    << "[" << RankToName(this->GetRank()) << "]";
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