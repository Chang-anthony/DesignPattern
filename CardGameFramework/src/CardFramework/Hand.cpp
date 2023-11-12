#include "../include/CardFramework/Hand.hpp"
#include "../include/CardFramework/Card.hpp"
#include "../include/utils/utils.h"

Hand::Hand(/* args */)
{
    this->hand = std::vector<Card*>();
}

void Hand::AddCard(Card* card)
{
    utils::RequireNonNull(card);
    this->hand.push_back(card);
}

std::vector<Card*> Hand::GetHandCard()
{
    return this->hand;
}

void Hand::SetHandCard(std::vector<Card*> card)
{
    this->hand = card;
}

Hand::~Hand()
{
}