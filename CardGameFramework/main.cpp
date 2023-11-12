/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "../include/ShowDown/Showdown.hpp"
#include "../include/CardFramework/Player.hpp"
#include "../include/CardFramework/Deck.hpp"
#include "../include/ShowDown/Showdown.hpp"
#include "../include/ShowDown/ShowDownHumanPlayer.hpp"
#include "../include/ShowDown/ShowDownAIPlayer.hpp"
#include "../include/ShowDown/ShowDownCard.hpp"
#include "../include/ShowDown/Rank.hpp"
#include "../include/ShowDown/Suit.hpp"
#include "../include/CardFramework/Card.hpp"
#include "../include/CardFramework/CardGame.hpp"

int main(int argc, char **argv)
{
    Player* P1 = new ShowDownHumanPlayer();
    Player* P2 = new ShowDownAIPlayer();
    Player* P3 = new ShowDownAIPlayer();
    Player* P4 = new ShowDownAIPlayer();

    std::vector<Player*> players = std::vector<Player*>();
    players.push_back(P1);
    players.push_back(P2);
    players.push_back(P3);
    players.push_back(P4);

    Deck* deck = new Deck(ShowDownCard::GenCards());

    Showdown* showdown = new Showdown(players,deck);

    showdown->GameStart();

    std::cout << "按下 Enter 鍵已結束遊戲" << std::endl;
    std::system("pause");
    return 0;
}