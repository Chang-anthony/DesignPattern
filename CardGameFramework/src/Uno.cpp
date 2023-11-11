#include "../include/Uno.hpp"
#include "../include/Deck.hpp"
#include "../include/Player.hpp"
#include "../include/Hand.hpp"
#include "../include/Card.hpp"
#include "../include/UnoPlayer.hpp"
#include "../include/UnoCard.hpp"
#include <algorithm>
#include <typeinfo>
#include <random>

//TODO:Uno game 

Uno::Uno(std::vector<Player*> players,Deck* deck):CardGame(players,deck)
{
    this->newCard = nullptr;
    this->passCards = std::vector<Card*>();
}

Uno::~Uno()
{
}