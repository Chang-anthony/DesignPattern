#include "../include/ShowDown/ShowDownCard.hpp"

ShowDownCard::ShowDownCard(Rank rank,Suit suit):Card(),rank(rank),suit(suit)
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

std::vector<Card*> ShowDownCard::GenCards()
{
    std::vector<Card*> cards = std::vector<Card*>();
    //A
    cards.push_back(new ShowDownCard(Rank::A,Suit::Club));
    cards.push_back(new ShowDownCard(Rank::A,Suit::Diamond));
    cards.push_back(new ShowDownCard(Rank::A,Suit::Heart));
    cards.push_back(new ShowDownCard(Rank::A,Suit::Spade));
    //2
    cards.push_back(new ShowDownCard(Rank::Sec,Suit::Club));
    cards.push_back(new ShowDownCard(Rank::Sec,Suit::Diamond));
    cards.push_back(new ShowDownCard(Rank::Sec,Suit::Heart));
    cards.push_back(new ShowDownCard(Rank::Sec,Suit::Spade));
    //3
    cards.push_back(new ShowDownCard(Rank::Thr,Suit::Club));
    cards.push_back(new ShowDownCard(Rank::Thr,Suit::Diamond));
    cards.push_back(new ShowDownCard(Rank::Thr,Suit::Heart));
    cards.push_back(new ShowDownCard(Rank::Thr,Suit::Spade));
    //4
    cards.push_back(new ShowDownCard(Rank::Four,Suit::Club));
    cards.push_back(new ShowDownCard(Rank::Four,Suit::Diamond));
    cards.push_back(new ShowDownCard(Rank::Four,Suit::Heart));
    cards.push_back(new ShowDownCard(Rank::Four,Suit::Spade));
    //5
    cards.push_back(new ShowDownCard(Rank::Five,Suit::Club));
    cards.push_back(new ShowDownCard(Rank::Five,Suit::Diamond));
    cards.push_back(new ShowDownCard(Rank::Five,Suit::Heart));
    cards.push_back(new ShowDownCard(Rank::Five,Suit::Spade));
    //6
    cards.push_back(new ShowDownCard(Rank::Six,Suit::Club));
    cards.push_back(new ShowDownCard(Rank::Six,Suit::Diamond));
    cards.push_back(new ShowDownCard(Rank::Six,Suit::Heart));
    cards.push_back(new ShowDownCard(Rank::Six,Suit::Spade));
    //7
    cards.push_back(new ShowDownCard(Rank::Seven,Suit::Club));
    cards.push_back(new ShowDownCard(Rank::Seven,Suit::Diamond));
    cards.push_back(new ShowDownCard(Rank::Seven,Suit::Heart));
    cards.push_back(new ShowDownCard(Rank::Seven,Suit::Spade));
    //8
    cards.push_back(new ShowDownCard(Rank::Eight,Suit::Club));
    cards.push_back(new ShowDownCard(Rank::Eight,Suit::Diamond));
    cards.push_back(new ShowDownCard(Rank::Eight,Suit::Heart));
    cards.push_back(new ShowDownCard(Rank::Eight,Suit::Spade));
    //9
    cards.push_back(new ShowDownCard(Rank::Night,Suit::Club));
    cards.push_back(new ShowDownCard(Rank::Night,Suit::Diamond));
    cards.push_back(new ShowDownCard(Rank::Night,Suit::Heart));
    cards.push_back(new ShowDownCard(Rank::Night,Suit::Spade));
    //10
    cards.push_back(new ShowDownCard(Rank::Ten,Suit::Club));
    cards.push_back(new ShowDownCard(Rank::Ten,Suit::Diamond));
    cards.push_back(new ShowDownCard(Rank::Ten,Suit::Heart));
    cards.push_back(new ShowDownCard(Rank::Ten,Suit::Spade));
    //11
    cards.push_back(new ShowDownCard(Rank::J,Suit::Club));
    cards.push_back(new ShowDownCard(Rank::J,Suit::Diamond));
    cards.push_back(new ShowDownCard(Rank::J,Suit::Heart));
    cards.push_back(new ShowDownCard(Rank::J,Suit::Spade));
    //12
    cards.push_back(new ShowDownCard(Rank::Q,Suit::Club));
    cards.push_back(new ShowDownCard(Rank::Q,Suit::Diamond));
    cards.push_back(new ShowDownCard(Rank::Q,Suit::Heart));
    cards.push_back(new ShowDownCard(Rank::Q,Suit::Spade));
    //13
    cards.push_back(new ShowDownCard(Rank::K,Suit::Club));
    cards.push_back(new ShowDownCard(Rank::K,Suit::Diamond));
    cards.push_back(new ShowDownCard(Rank::K,Suit::Heart));
    cards.push_back(new ShowDownCard(Rank::K,Suit::Spade));

    return cards;
}

ShowDownCard::~ShowDownCard()
{

}