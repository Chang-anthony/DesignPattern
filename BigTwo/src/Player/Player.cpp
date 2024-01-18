#include <Player.hpp>
#include <Deck.hpp>
#include <HandCard.hpp>


Player::Player()
{
    this->handcard = new HandCard();
    this->name;
}

bool Player::isHandCardEmpty()
{
    return this->handcard->GetCards().size() == 0;
}

void Player::Deal(Deck* deck)
{
    this->handcard->AddCard(deck->DrawCard());
}

void Player::SetHandCard(HandCard* handcard)
{
    this->handcard = handcard;
}

void Player::SetName(std::string name)
{
    this->name = name;
}

HandCard* Player::GetHandCard()
{
    return this->handcard;
}

std::string Player::GetName()
{
    return this->name;
}

Player::~Player()
{
}