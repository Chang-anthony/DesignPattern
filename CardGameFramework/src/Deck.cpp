#include "../include/Deck.hpp"
#include "../include/Card.hpp"
#include <algorithm>
#include <random>
#include <chrono> //std::chrono::system_clock

Deck::Deck(std::vector<Card*> cards)
{
    //只要有牌組一定有牌，但有牌可能是單張的所以並不是複合關聯
    this->cards = cards;
}

//Draw Top card
Card* Deck::DrawCard()
{
    Card* card = this->cards.front();
    this->cards.erase(this->cards.begin());

    return card;
}

//洗牌
void Deck::Suffle()
{
    std::srand(unsigned(std::time(0)));

    auto myrandom = [](int i){ return std::rand() % i;};

    //obtain a time-base seed
    //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    auto first = this->cards.begin();
    auto last = this->cards.end();

    for(auto i = (last - first) - 1; i > 0; --i)
    {
        //std::uniform_int_distribution<decltype(i)> d(0,i);
        std::swap(first[i],first[myrandom(i)]);
    }
}

Deck* Deck::ReFresh(std::vector<Card*> cards)
{
    return new Deck(cards);
}

void Deck::RenderCards()
{
    for(auto card:this->cards)
        card->render();
}


std::vector<Card*> Deck::GetCards()
{
    return this->cards;
}

void Deck::SetCards(std::vector<Card*> cards)
{
    this->cards = cards;
}

Deck::~Deck()
{
}