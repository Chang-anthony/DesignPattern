#include <Card.hpp>
#include <HandCard.hpp>

HandCard::HandCard(/* args */)
{
    this->handcard = std::vector<Card*>();
}

void HandCard::AddCard(Card* card)
{
    this->handcard.push_back(card);
}

void HandCard::SetCards(std::vector<Card*> cards)
{
    this->handcard.clear();
    this->handcard = cards;
}

std::vector<Card*> HandCard::GetCards()
{
    return this->handcard;
}

HandCard::~HandCard()
{
}