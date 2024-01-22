#ifndef _BIGTWO_H_
#define _BIGTWO_H_

#include <iostream>
#include <vector>
#include <string>
#include <utils.h>

class Deck;
class Round;
class Player;
class Card;
class CardPatternHandler;

class Bigtwo
{
private:
    /* data */
    std::vector<Player*> players;
    std::vector<Round*> rounds;
    Deck* deck;
    CardPatternHandler* handler;

    void AddRound(Round* round);
    void doDeal();
    Player* FristPlay();
    Round* newRound(Player* topplayer);
    Round* FirstRound(Player* topplayer);

public:
    Bigtwo(Deck* deck,std::vector<Player*> players, CardPatternHandler* handler);
    ~Bigtwo();

    void GameStart();
    void GameEnd();
    bool isEnd();
    bool CampareHandle(std::vector<Card*> cards, std::vector<Card*> topplay);
    bool vaildHandle(std::vector<Card*> cards);
    std::string PatternNameHandle(std::vector<Card*> cards);

    //helper function
    void Render(Player* play, std::vector<Card*> cards);

    //getter
    std::vector<Player*> GetPlayers();
    Deck* GetDeck();

    //setter
    void SetPlayers(std::vector<Player*> players);
    void SetDeck(Deck* deck);
    void SetPatternHandler(CardPatternHandler* handler);
};

#endif /* _BIGTWO_H_ */
