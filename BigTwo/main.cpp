/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "Player.hpp"
#include <Card.hpp>
#include <Deck.hpp>
#include <utils.h>
#include <fstream>
#include <sstream>
#include <FileLine.hpp>
#include <FileIterator.hpp>
#include <BigTwo_paser.hpp>
#include <tuple>
#include <CardPatternHandler.hpp>
#include <SingleHandler.hpp>
#include <PairHandler.hpp>
#include <FullHouseHandler.hpp>
#include <StraightHandler.hpp>
#include <HumanPlayer.hpp>
#include <Bigtwo.hpp>


void TEST_BIGTWO(std::string& input)
{
    //parser input file
    std::tuple<std::vector<Card*>, std::vector<std::string>, 
            std::vector<std::vector<int>>> results = BigTwo_paser::parser(input);

    std::vector<Card*> cards = std::get<0>(results);
    std::vector<std::string> names = std::get<1>(results);
    std::vector<std::vector<int>> plays = std::get<2>(results);

    // for (auto play : plays)
    // {
    //     for (auto n : play)
    //     {
    //         std::cout << n << " ";
    //     }

    //     std::cout << std::endl;
    // }
    
    //initial game condition
    Deck* deck = new Deck();
    deck->SetCards(cards);

    Player* player1 = new HumanPlayer();
    Player* player2 = new HumanPlayer();
    Player* player3 = new HumanPlayer();
    Player* player4 = new HumanPlayer();

    std::vector<Player*> players = std::vector<Player*>();
    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);
    players.push_back(player4);

    for (int i = 0; i < players.size(); i++)
    {
        players[i]->SetName(names[i]);
    }

    CardPatternHandler* newhandler = new SingleHandler(
                                        new PairHandler(
                                            new FullHouseHandler(
                                                new StraightHandler(nullptr))));

    Bigtwo* game = new Bigtwo(deck, players, newhandler);
    game->RunTest(game, plays);
}

static inline std::vector<std::string> readFile(std::string path) 
{
    std::vector<std::string> lines = std::vector<std::string>();
    std::ifstream inputFile(path);
    
    if(inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            lines.push_back(line);
            std::cout << line << std::endl;
        }
        inputFile.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
    return lines;
}

static inline std::vector<Card*> cardparser(std::string strs)
{
    std::vector<std::string> tokens = std::vector<std::string>();
    std::istringstream iss(strs);
    std::string token;

    while (iss >> token)
    {
        tokens.push_back(token);
    }

    std::vector<Card*> cards = std::vector<Card*>();
    for (auto token: tokens)
    {
        int count = 0;
        std::string rank;
        std::string suit;
        while (count < token.length())
        {
            while(token[count] != '[') {
                suit += token[count];
                count++;
            }
            while(token[count] != ']') {
                if(token[count] != '[')
                    rank += token[count];
                count++;
            }
            count++;
        }
        
        Card* card = Card::GenCardFromChar(rank, suit);
        cards.push_back(card);
    }
    
    return cards;
}

static inline void F(FileIterator& A)
{
    // std::cout << "in" << std::endl;
}

int main()
{
    //FileIterator *test = new FileIterator("C:/Users/JCCanthony/Desktop/DesignPatternCode/BigTwo/test/testSet/always-play-first-card.in");
    //fullhouse
    // std::tuple<std::vector<Card*>, std::vector<std::string>, 
    //             std::vector<std::vector<int>>> results = BigTwo_paser::parser("../BigTwo/test/testSet/fullhouse.in");
    

    // std::vector<Card*> cards = std::get<0>(results);
    // std::vector<std::string> names = std::get<1>(results);
    // std::vector<std::vector<int>> plays = std::get<2>(results);

    // std::cout << "cards" << std::endl;
    // Deck* deck = new Deck();
    // deck->SetCards(cards);
    // deck->RenderCards();

    // std::cout << std::endl << "name" << std::endl;
    // for (auto name: names)
    // {
    //     std::cout << name << std::endl;
    // }

    // std::cout << "play" << std::endl;
    // for (auto play: plays)
    // {
    //     for (auto n : play)
    //     {
    //         std::cout << n << " ";
    //     }
    //     std::cout << std::endl;
    // }

    //always-play-first-card test ok
    //fullhouse
    std::string test1 = "../BigTwo/test/testSet/always-play-first-card.in";
    std::string test2 = "../BigTwo/test/testSet/fullhouse.in";
    std::cout << "test1" << std::endl;
    TEST_BIGTWO(test1);
    std::cout << "test2" << std::endl;
    TEST_BIGTWO(test2);
    
    std::cout << "按下 Enter 鍵已結束遊戲" << std::endl;
    std::system("pause");
    return 0;
}