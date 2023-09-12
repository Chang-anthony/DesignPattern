#include "../include/ExchangeCard.hpp"
#include "../include/Player.hpp"

ExchangeCard::ExchangeCard(Player* player1,Player* player2):player1(player1),player2(player2)
{
    int round = 3;
}

Player* ExchangeCard::Show(Player* player)
{
    return player1 == player ? player2 : player1;
}

Player* ExchangeCard::GetPlayer1()
{
    return this->player1;
}

Player* ExchangeCard::GetPlayer2()
{
    return this->player2;
}

int ExchangeCard::GetRound()
{
   return this->round;
}

void ExchangeCard::SetPlayer1(Player* player1)
{
    this->player1 = player1;
}

void ExchangeCard::SetPlayer2(Player* player2)
{
    this->player2 = player2;
}

void ExchangeCard::SetRound(int round)
{
    this->round = round;
}

ExchangeCard::~ExchangeCard()
{

}