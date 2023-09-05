#include "../include/Player.hpp"
#include "../include/Deck.hpp"


Player::Player(bool Human)
{
    this->name = "";
    this->Exchange = true;
    this->IsHuman = Human;
    this->point = 0;
    this->handcards = std::vector<Card*>();
}

void Player::NameSelf()
{
    std::cout << "Please Name Your Self :";
    std::string InputName;
    std::cin >> InputName;
    this->SetName(InputName);
}

void Player::DrawCard(Deck* deck)
{
    std::cout << "玩家 :" << this->GetName() << "從牌堆抽牌" << std::endl;
    Card* card = deck->DrawCard();
    this->handcards.push_back(card);
    //handle handcard length bigger to 13
    utils::SizeShouldSmaller(this->handcards,13);
}


std::string Player::GetName()
{
    return this->name;
}

std::vector<Card*> Player::GetHandCards()
{
    return this->handcards;
}

bool Player::GetIsHuman()
{
    return this->IsHuman;
}

bool Player::GetExchange()
{
    return this->Exchange;
}

int Player::GetPoint()
{
    return this->point;
}

void Player::SetName(std::string name)
{
    this->name = name;
}

void Player::SetHandCards(std::vector<Card*> handcards)
{
    this->handcards = handcards;
}

void Player::SetIsHuman(bool IsHuman)
{
    this->IsHuman = IsHuman;
}

void Player::SetExchange(bool exchange)
{
    this->Exchange = exchange;
}

void Player::SetPoint(int point)
{
    this->point = point;
}

Player::~Player()
{

}