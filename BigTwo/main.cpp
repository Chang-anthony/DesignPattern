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


//TODO: need to wirte simple test to test Round function
int main()
{
    std::vector<std::string> inputs = readFile("C:/Users/JCCanthony/Desktop/DesignPatternCode/BigTwo/test/testSet/always-play-first-card.in");
    
    std::vector<Card*> cards = cardparser(inputs[0]);
    Deck* deck = new Deck();
    deck->SetCards(cards);
    
    deck->RenderCards();
    

    // std::cout << "Test Input Multiple Numbers" << std::endl;
    // std::vector<int> inputs = utils::InputMultipleNums();

    // for(auto num : inputs){
    //     std::cout << num << " ";
    // }
    // std::cout << std::endl;
    
    std::cout << "按下 Enter 鍵已結束遊戲" << std::endl;
    std::system("pause");
    return 0;
}