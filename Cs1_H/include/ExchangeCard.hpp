#ifndef _EXCHANGECARD_H_
#define _EXCHANGECARD_H_

class Player;

class ExchangeCard
{
private:
    Player* player1;
    Player* player2;
    int round;
public:
    ExchangeCard(Player* player1,Player* player2);
    ~ExchangeCard();

    //getter
    Player* GetPlayer1();
    Player* GetPlayer2();
    int GetRound();

    //setter
    void SetPlayer1(Player* player1);
    void SetPlayer2(Player* player2);
    void SetRound(int round);
};

#endif /* _EXCHANGE_H_ */
