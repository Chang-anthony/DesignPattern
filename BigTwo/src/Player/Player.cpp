#include <Player.hpp>
#include <Deck.hpp>
#include <HandCard.hpp>
#include <Card.hpp>
#include <iostream>
#include <algorithm>


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

void Player::RenderHandCard()
{
    for(int i = 0 ; i < this->handcard->GetCards().size() ; i++)
        std::cout<< i << "    ";
    std::cout << std::endl;
    for(auto card:this->handcard->GetCards())
    {
        card->render();
        std::cout << " ";
    }
    std::cout << std::endl;
}

//TODO:need to test
void Player::RemoveCardFromHand(std::vector<Card*> played)
{
    std::vector<Card*> copy = this->handcard->GetCards();
    for(auto play:played)
    {
        copy.erase(std::remove_if(copy.begin(), copy.end(),[play](Card* card)
        {
            return play == card;
        }),copy.end());
    }
    this->handcard->SetCards(copy);
}

void Player::SortHandCard()
{
    std::vector<Card*> copy = this->handcard->GetCards();

    struct cmp{
        bool operator()(Card* A, Card* B)
        {
            return RankToNumber(A->GetRank()) < RankToNumber(B->GetRank());
        }
    }cmp;

    std::sort(copy.begin(), copy.end(), cmp);
    this->handcard->SetCards(copy);
}

bool Player::verfiyInput(std::vector<int> want_play)
{
    int max_size = this->handcard->GetCards().size();
    bool verfiy = true;

    for(auto input: want_play){
        if(input >= max_size){
            verfiy = false;
            break;
        }
    }

    return verfiy;
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