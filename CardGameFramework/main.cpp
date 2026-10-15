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
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

int main(int argc, char **argv)
{
#ifdef _WIN32
    // 原始碼是 UTF-8，將 console 輸出改為 UTF-8 才能正確顯示中文
    SetConsoleOutputCP(CP_UTF8);
#endif
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