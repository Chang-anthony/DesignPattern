#include "../include/Card.hpp"
#include "../include/Deck.hpp"

Card::Card(Rank rank,Suit suit):rank(rank),suit(suit),deck(nullptr)
{
    
}

Card::Card(Rank rank,Suit suit,Deck* deck):rank(rank),suit(suit),deck(deck)
{

}

void Card::render()
{
    std::cout << SuitToName(this->GetSuit())  
    << "[" << RankToName(this->GetRank()) << "]" << std::endl;
}

/*if this card bigger than card return true;*/
bool Card::IsBigger(Card* card)
{
    bool isbigger = true;
    std::string rank1 = RankToString(this->GetRank());
    std::string rank2 = RankToString(card->GetRank());

    if( rank1 == rank2)
    {
        std::string suit1 = SuitToString(this->GetSuit());
        std::string suit2 = SuitToString(card->GetSuit());

        if(std::stoi(suit1) < std::stoi(suit2))
            isbigger = false;
    }
    else
    {
        if(rank1 != "1" && rank2 != "1")
        {
            if(std::stoi(rank1) < std::stoi(rank2))
                isbigger = false;
        }
        else
        {
            if(rank2 == "1")
                isbigger = false;
        }
    }

    return isbigger;
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