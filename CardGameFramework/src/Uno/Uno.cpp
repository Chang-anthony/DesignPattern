#include "../include/Uno/Uno.hpp"
#include "../include/CardFramework/Deck.hpp"
#include "../include/CardFramework/Player.hpp"
#include "../include/CardFramework/Hand.hpp"
#include "../include/CardFramework/Card.hpp"
#include "../include/Uno/UnoPlayer.hpp"
#include "../include/Uno/UnoCard.hpp"
#include <algorithm>
#include <typeinfo>
#include <random>


Uno::Uno(std::vector<Player*> players,Deck* deck):CardGame(players,deck)
{
    this->newCard = nullptr;
    this->passCards = std::vector<Card*>();
    this->gameEnd = false;
    this->drawcard = 0;
}

void Uno::Round()
{
    for(auto p:this->GetPlayers())
    {
        std::vector<Card*> vaild = std::vector<Card*>();
        //check can pass card
        for(auto hand:p->GetHand()->GetHandCard())
        {
            if(this->IsVaild(hand))
            {
                vaild.push_back(hand);
            }
        }

        if(vaild.size() == 0)
        {
            if(this->GetDeck()->GetCards().size() == 0)
            {
                this->passCards.pop_back();
                this->GetDeck()->SetCards(this->passCards);
                this->GetDeck()->Suffle();
                this->passCards.clear();
            }
            Card* draw = this->GetDeck()->DrawCard();
            p->AddCard(draw);
        }
        else
        {
            //show card
            Card* show = p->takeTurn(vaild);
            std::cout<< "玩家 :" << p->GetName() << "出了 :";
            show->render();
            std::cout << std::endl;

            //remove hand card
            std::vector<Card*> handcards = p->GetHand()->GetHandCard();
            p->GetHand()->SetHandCard(utils::RemoveObjectFromVector(handcards,show));
        }
        //handle if player handcard is all pass 
        if(p->GetHand()->GetHandCard().size() == 0)
        {   
            this->gameEnd = true;
            break;
        }
    }
}

bool Uno::DrawCardEnd()
{
    this->drawcard++;
    if(this->drawcard > 5)
        this->newCard = this->GetDeck()->DrawCard();
    return this->drawcard <= 5;
}

bool Uno::IsGameEnd()
{
    return this->gameEnd;
}

Player* Uno::GetWinner()
{
    Player* winner = nullptr;
    for(auto p:this->GetPlayers())
    {
        if(p->GetHand()->GetHandCard().size() == 0)
            winner = p;
    }
    return winner;
}

bool Uno::IsVaild(Card* card)
{
    UnoCard* c1 = dynamic_cast<UnoCard*>(this->newCard);
    UnoCard* c2 = dynamic_cast<UnoCard*>(card);

    return c1->IsSame(c2);
}

Uno::~Uno()
{
}