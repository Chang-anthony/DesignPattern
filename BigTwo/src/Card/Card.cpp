#include "Card.hpp"
#include "Deck.hpp"


Card::Card(Rank rank,Suit suit):rank(rank),suit(suit),deck(nullptr)
{

}

Card::Card(Rank rank,Suit suit,Deck* deck):rank(rank),suit(suit),deck(deck)
{

}

Card* Card::GenCardFromChar(std::string rank, std::string suit)
{
    if(CharToRank(rank) != Rank::None && CharToSuit(suit) != Suit::None)
    {
        Rank r = CharToRank(rank);
        Suit s = CharToSuit(suit);
        return new Card(r, s);
    } else 
        return nullptr;
}

bool Card::isBigger(Card* card)
{
    int number1 = RankToNumber(this->GetRank());
    int number2 = RankToNumber(card->GetRank());
    
    if(number1 != number2)
        return number1 > number2; 
    else
    {
        int suit1 = SuitToNumber(this->GetSuit());
        int suit2 = SuitToNumber(card->GetSuit());
        return suit1 > suit2;
    }
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