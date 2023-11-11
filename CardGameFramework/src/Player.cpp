#include "../include/Player.hpp"
#include "../include/Hand.hpp"
#include "../include/Card.hpp"


Player::Player()
{
    this->name = "";
    this->hand = new Hand();
}

void Player::AddCard(Card* card)
{
    this->hand->AddCard(card);
}

Hand* Player::GetHand()
{
    return this->hand;
}

void Player::SetHand(Hand* hand)
{
    this->hand = hand;
}

std::string Player::GetName()
{
    return this->name;
}

void Player::SetName(std::string name)
{
    this->name = name;
}

Player::~Player()
{
}



