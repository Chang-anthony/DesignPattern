#include "Card.hpp"
#include "Deck.hpp"
#include <algorithm>
#include <random>
#include <chrono> //std::chrono::system_clock

Deck::Deck(/* args */)
{
    //只要有牌組一定有牌，但有牌可能是單張的所以並不是複合關聯
    this->cards = std::vector<Card*>();
    //A
    this->cards.push_back(new Card(Rank::A,Suit::Club,this));
    this->cards.push_back(new Card(Rank::A,Suit::Diamond,this));
    this->cards.push_back(new Card(Rank::A,Suit::Heart,this));
    this->cards.push_back(new Card(Rank::A,Suit::Spade,this));
    //2
    this->cards.push_back(new Card(Rank::Sec,Suit::Club,this));
    this->cards.push_back(new Card(Rank::Sec,Suit::Diamond,this));
    this->cards.push_back(new Card(Rank::Sec,Suit::Heart,this));
    this->cards.push_back(new Card(Rank::Sec,Suit::Spade,this));
    //3
    this->cards.push_back(new Card(Rank::Thr,Suit::Club,this));
    this->cards.push_back(new Card(Rank::Thr,Suit::Diamond,this));
    this->cards.push_back(new Card(Rank::Thr,Suit::Heart,this));
    this->cards.push_back(new Card(Rank::Thr,Suit::Spade,this));
    //4
    this->cards.push_back(new Card(Rank::Four,Suit::Club,this));
    this->cards.push_back(new Card(Rank::Four,Suit::Diamond,this));
    this->cards.push_back(new Card(Rank::Four,Suit::Heart,this));
    this->cards.push_back(new Card(Rank::Four,Suit::Spade,this));
    //5
    this->cards.push_back(new Card(Rank::Five,Suit::Club,this));
    this->cards.push_back(new Card(Rank::Five,Suit::Diamond,this));
    this->cards.push_back(new Card(Rank::Five,Suit::Heart,this));
    this->cards.push_back(new Card(Rank::Five,Suit::Spade,this));
    //6
    this->cards.push_back(new Card(Rank::Six,Suit::Club,this));
    this->cards.push_back(new Card(Rank::Six,Suit::Diamond,this));
    this->cards.push_back(new Card(Rank::Six,Suit::Heart,this));
    this->cards.push_back(new Card(Rank::Six,Suit::Spade,this));
    //7
    this->cards.push_back(new Card(Rank::Seven,Suit::Club,this));
    this->cards.push_back(new Card(Rank::Seven,Suit::Diamond,this));
    this->cards.push_back(new Card(Rank::Seven,Suit::Heart,this));
    this->cards.push_back(new Card(Rank::Seven,Suit::Spade,this));
    //8
    this->cards.push_back(new Card(Rank::Eight,Suit::Club,this));
    this->cards.push_back(new Card(Rank::Eight,Suit::Diamond,this));
    this->cards.push_back(new Card(Rank::Eight,Suit::Heart,this));
    this->cards.push_back(new Card(Rank::Eight,Suit::Spade,this));
    //9
    this->cards.push_back(new Card(Rank::Night,Suit::Club,this));
    this->cards.push_back(new Card(Rank::Night,Suit::Diamond,this));
    this->cards.push_back(new Card(Rank::Night,Suit::Heart,this));
    this->cards.push_back(new Card(Rank::Night,Suit::Spade,this));
    //10
    this->cards.push_back(new Card(Rank::Ten,Suit::Club,this));
    this->cards.push_back(new Card(Rank::Ten,Suit::Diamond,this));
    this->cards.push_back(new Card(Rank::Ten,Suit::Heart,this));
    this->cards.push_back(new Card(Rank::Ten,Suit::Spade,this));
    //11
    this->cards.push_back(new Card(Rank::J,Suit::Club,this));
    this->cards.push_back(new Card(Rank::J,Suit::Diamond,this));
    this->cards.push_back(new Card(Rank::J,Suit::Heart,this));
    this->cards.push_back(new Card(Rank::J,Suit::Spade,this));
    //12
    this->cards.push_back(new Card(Rank::Q,Suit::Club,this));
    this->cards.push_back(new Card(Rank::Q,Suit::Diamond,this));
    this->cards.push_back(new Card(Rank::Q,Suit::Heart,this));
    this->cards.push_back(new Card(Rank::Q,Suit::Spade,this));
    //13
    this->cards.push_back(new Card(Rank::K,Suit::Club,this));
    this->cards.push_back(new Card(Rank::K,Suit::Diamond,this));
    this->cards.push_back(new Card(Rank::K,Suit::Heart,this));
    this->cards.push_back(new Card(Rank::K,Suit::Spade,this));
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

Deck* Deck::ReFresh()
{
    return new Deck();
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