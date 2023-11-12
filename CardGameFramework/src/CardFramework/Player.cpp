#include "../include/CardFramework/Player.hpp"
#include "../include/CardFramework/Hand.hpp"
#include "../include/CardFramework/Card.hpp"


Player::Player()
{
    this->name = "";
    this->hand = new Hand();
}

void Player::AddCard(Card* card)
{
    this->hand->AddCard(card);
}

void Player::NameSelf()
{
    std::cout << "Please Name Your Self :";
    std::string InputName;
    std::cin >> InputName;
    this->SetName(InputName);
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



