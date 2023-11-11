#include "../include/ShowDownCard.hpp"
#include "../include/Deck.hpp"

ShowDownCard::ShowDownCard(Rank rank,Suit suit):Card(),rank(rank),suit(suit),deck(nullptr)
{
    
}

ShowDownCard::ShowDownCard(Rank rank,Suit suit,Deck* deck):Card(),rank(rank),suit(suit),deck(deck)
{

}

void ShowDownCard::render()
{
    std::cout << SuitToName(this->GetSuit())[0]  
    << "[" << RankToName(this->GetRank()) << "]";
}

/*if this card bigger than card return true;*/
bool ShowDownCard::IsBigger(ShowDownCard* card)
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

Rank ShowDownCard::GetRank()
{
    return this->rank;
}

Suit ShowDownCard::GetSuit()
{
    return this->suit;
}

void ShowDownCard::SetRank(Rank rank)
{
    this->rank = rank;
}

void ShowDownCard::SetSuit(Suit suit)
{
    this->suit = suit;
}

ShowDownCard::~ShowDownCard()
{

}