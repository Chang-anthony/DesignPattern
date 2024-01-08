#include <iostream>
#include <gtest/gtest.h>
#include "gtest/gtest-spi.h"
#include <Deck.hpp>
#include <Suit.hpp>
#include <Player.hpp>
#include <Rank.hpp>
#include <HumanPlayer.hpp>
#include <AIPlayer.hpp>
#include <Card.hpp>
#include <HandCard.hpp>
#include <CardPatternHandler.hpp>
#include <SingleHandler.hpp>
#include <PairHandler.hpp>
#include <FullHouseHandler.hpp>
#include <StraightHandler.hpp>


TEST(Deck,DeckTest)
{
    Deck* deck = new Deck();
    std::vector<Card*> cards = deck->GetCards();
    deck->Suffle();
    std::vector<Card*> cards2 = deck->GetCards();
    EXPECT_NE(cards[0],cards2[0]);
}


TEST(HandCard,HandCardTEST)
{
    Player* player = new HumanPlayer();
    Deck* deck = new Deck();
    deck->Suffle();

    player->Deal(deck);

    std::vector<Card*> deckcards = deck->GetCards();
    std::vector<Card*> handcards = player->GetHandCard()->GetCards();

    EXPECT_EQ(1,handcards.size());
    EXPECT_EQ(51,deckcards.size());
}

TEST(SingleHandler,SingleHandler_Test)
{
    CardPatternHandler* handler = new SingleHandler( new PairHandler( new FullHouseHandler(new StraightHandler(nullptr))));

    Rank five = Rank::Five;
    Rank A = Rank::A;
    Rank two = Rank::Sec;
    Rank K = Rank::K;


    Suit Spade = Suit::Spade;
    Suit Heart = Suit::Heart;
    Suit Diamond = Suit::Diamond;
    Suit Club = Suit::Club;

    Card* card1 = new Card(five,Spade);
    Card* card2 = new Card(A,Club);
    Card* card3 = new Card(two,Heart);
    Card* card4 = new Card(K,Diamond);

    EXPECT_EQ(handler->PatternNameHandle({card1}),"單張");
    EXPECT_EQ(handler->PatternNameHandle({card2}),"單張");
    EXPECT_EQ(handler->PatternNameHandle({card3}),"單張");
    EXPECT_EQ(handler->PatternNameHandle({card4}),"單張");
    EXPECT_EQ(handler->PatternNameHandle({card2,card4}),"");

    EXPECT_NE(handler->PatternNameHandle({card2,card4}),"單張");
    EXPECT_NE(handler->PatternNameHandle({card1,card3}),"單張");
    EXPECT_NE(handler->PatternNameHandle({card3,card2}),"單張");
}


TEST(PairHandler,PairHandler_Test)
{
    CardPatternHandler* handler = new SingleHandler( new PairHandler( new FullHouseHandler(new StraightHandler(nullptr))));

    Rank five = Rank::Five;
    Rank A = Rank::A;
    Rank two = Rank::Sec;
    Rank K = Rank::K;


    Suit Spade = Suit::Spade;
    Suit Heart = Suit::Heart;
    Suit Diamond = Suit::Diamond;
    Suit Club = Suit::Club;

    Card* card1 = new Card(A,Spade);
    Card* card2 = new Card(A,Club);
    Card* card3 = new Card(two,Heart);
    Card* card4 = new Card(two,Diamond);

    Card* card5 = new Card(two,Heart);
    Card* card6 = new Card(K,Diamond);

    EXPECT_EQ(handler->PatternNameHandle({card1,card2}),"對子");
    EXPECT_EQ(handler->PatternNameHandle({card3,card4}),"對子");
    EXPECT_EQ(handler->PatternNameHandle({card3}),"單張");
    EXPECT_EQ(handler->PatternNameHandle({card4}),"單張");
    EXPECT_EQ(handler->PatternNameHandle({card2,card4}),"");

    EXPECT_NE(handler->PatternNameHandle({card1,card2}),"單張");
    EXPECT_NE(handler->PatternNameHandle({card3,card4}),"葫蘆");
    EXPECT_NE(handler->PatternNameHandle({card3,card2}),"對子");
}




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

