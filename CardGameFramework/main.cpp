/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "../include/Showdown.hpp"
#include "../include/Player.hpp"
#include "../include/Deck.hpp"
#include "../include/AIPlayer.hpp"
#include "../include/HumanPlayer.hpp"
#include "../include/Rank.hpp"
#include "../include/Suit.hpp"
#include "../include/Card.hpp"


//TODO: need to wirte simple test to test Round function
int main(int argc, char **argv)
{
    HumanPlayer* P1 = new HumanPlayer();
    AIPlayer* P2 = new AIPlayer();
    AIPlayer* P3 = new AIPlayer();
    AIPlayer* P4 = new AIPlayer();

    std::vector<Player*> players = std::vector<Player*>();
    players.push_back(P1);
    players.push_back(P2);
    players.push_back(P3);
    players.push_back(P4);

    Deck* deck = new Deck();

    Showdown* showdown = new Showdown(deck,players);

    showdown->GameStart();

    showdown->NameHimSelf();

    showdown->DoShuffle();

    showdown->DrawCard();

    for(int i = 0 ; i < 13; i++)
    {
        showdown->Round();
        std::cout << std::endl;
    }

    showdown->GameEnd();
    
    std::cout << "按下 Enter 鍵已結束遊戲" << std::endl;
    std::system("pause");
    return 0;
}