#include <BigTwo_paser.hpp>
#include <FileIterator.hpp>
#include <Card.hpp>
#include <sstream>
#include <algorithm>

BigTwo_paser::BigTwo_paser()
{
}

std::tuple<std::vector<Card*>, std::vector<std::string>, 
        std::vector<std::vector<int>>> BigTwo_paser::parser(const std::string& filepath)
{
    FileIterator it = FileIterator(filepath);
    int count = 0;
    std::vector<std::string> lines = std::vector<std::string>();
    while (!it)
    {
        lines.push_back(*it);
        ++it;
    }
    lines.push_back(*it);

    std::vector<Card*> cards = BigTwo_paser::cardparser(lines[0]);
    std::reverse(cards.begin(), cards.end());
    lines.erase(lines.begin());
    count++;

    std::vector<std::string> names = std::vector<std::string>();
    while(count < 5)
    {
        names.push_back(lines[0]);
        lines.erase(lines.begin());
        count++;
    }

    std::vector<std::vector<int>> plays = BigTwo_paser::playparser(lines);
    
    return std::tuple<std::vector<Card*>, std::vector<std::string>, std::vector<std::vector<int>>>(cards, names, plays);
}

inline std::vector<std::vector<int>> BigTwo_paser::playparser(std::vector<std::string>& strs)
{
    std::vector<std::vector<int>> plays = std::vector<std::vector<int>>();
    int count = 0;
    for (auto str : strs)
    {
        std::istringstream iss(str);
        int input;
        plays.push_back({});

        while (iss >> input)
        {
            plays[count].push_back(input);
        }
        count++;
    }

    return plays;
}

inline std::vector<Card*> BigTwo_paser::cardparser(std::string& strs)
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

BigTwo_paser::~BigTwo_paser()
{
}