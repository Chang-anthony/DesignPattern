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

TEST(SingleHandler,SingleHandlerPatternName_Test)
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


TEST(PairHandler,PairHandlerPatternName_Test)
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

    // std::string out1 = handler->PatternNameHandle({card1,card2});
    // std::string out2 = handler->PatternNameHandle({card3,card4});

    // std::cout << out1 << std::endl;
    // std::cout << out2 << std::endl;

    // std::cout << std::endl;

    EXPECT_EQ(handler->PatternNameHandle({card1,card2}),"對子");
    EXPECT_EQ(handler->PatternNameHandle({card3,card4}),"對子");
    EXPECT_EQ(handler->PatternNameHandle({card3}),"單張");
    EXPECT_EQ(handler->PatternNameHandle({card4}),"單張");
    EXPECT_EQ(handler->PatternNameHandle({card2,card4}),"");

    EXPECT_NE(handler->PatternNameHandle({card1,card2}),"單張");
    EXPECT_NE(handler->PatternNameHandle({card3,card4}),"葫蘆");
    EXPECT_NE(handler->PatternNameHandle({card3,card2}),"對子");
}

TEST(FullHouseHandler,FullHouseHandlerPatternName_Test)
{
    CardPatternHandler* handler = new SingleHandler( new PairHandler( new FullHouseHandler(new StraightHandler(nullptr))));

    Rank A = Rank::A;
    Rank two = Rank::Sec;
    Rank three = Rank::Thr;
    Rank four = Rank::Four;
    Rank five = Rank::Five;
    Rank six = Rank::Six;
    Rank K = Rank::K;

    Suit Spade = Suit::Spade;
    Suit Heart = Suit::Heart;
    Suit Diamond = Suit::Diamond;
    Suit Club = Suit::Club;

    Card* card1 = new Card(A,Spade);
    Card* card2 = new Card(A,Club);
    Card* card3 = new Card(A,Diamond);
    Card* card4 = new Card(two,Heart);
    Card* card5 = new Card(two,Diamond);

    Card* card6 = new Card(three,Club);
    Card* card7 = new Card(four,Heart);
    Card* card8 = new Card(five,Spade);
    Card* card9 = new Card(six,Club);

    Card* card10 = new Card(two,Heart);
    Card* card11 = new Card(K,Diamond);

    std::string out1 = handler->PatternNameHandle({card1,card2,card3,card4,card5});
    std::string out2 = handler->PatternNameHandle({card5,card6,card7,card8,card9});
    std::string out3 = handler->PatternNameHandle({card5,card6,card7,card11,card9});
    std::string out4 = handler->PatternNameHandle({card5,card6,card10,card8,card9});


    EXPECT_EQ(out1,"葫蘆");
    EXPECT_NE(out2,"");


    EXPECT_NE(out3,"葫蘆");
    EXPECT_NE(out4,"葫蘆");
}

TEST(StraightHandler,StraightHandlerPatternName_Test)
{
    CardPatternHandler* handler = new SingleHandler( new PairHandler( new FullHouseHandler(new StraightHandler(nullptr))));

    Rank A = Rank::A;
    Rank two = Rank::Sec;
    Rank three = Rank::Thr;
    Rank four = Rank::Four;
    Rank five = Rank::Five;
    Rank six = Rank::Six;
    Rank seven = Rank::Seven;
    Rank eight = Rank::Eight;
    Rank nine = Rank::Night;
    Rank ten = Rank::Ten;
    Rank J = Rank::J;
    Rank Q = Rank::Q;
    Rank K = Rank::K;

    Suit Spade = Suit::Spade;
    Suit Heart = Suit::Heart;
    Suit Diamond = Suit::Diamond;
    Suit Club = Suit::Club;

    Card* card1 = new Card(A,Spade);
    Card* card2 = new Card(A,Club);
    Card* card3 = new Card(A,Diamond);
    Card* card4 = new Card(two,Heart);
    Card* card5 = new Card(two,Diamond);
    Card* card6 = new Card(three,Club);
    Card* card7 = new Card(four,Heart);
    Card* card8 = new Card(five,Spade);
    Card* card9 = new Card(six,Club);

    Card* card10 = new Card(ten,Heart);
    Card* card11 = new Card(J,Diamond);
    Card* card12 = new Card(Q,Club);
    Card* card13 = new Card(K,Diamond);
    Card* card14 = new Card(A,Heart);
    

    std::string out1 = handler->PatternNameHandle({card1,card2,card3,card4,card5});
    std::string out2 = handler->PatternNameHandle({card5,card6,card7,card8,card9});
    std::string out3 = handler->PatternNameHandle({card5,card6,card7,card11,card9});
    std::string out4 = handler->PatternNameHandle({card5,card6,card10,card8,card9});
    std::string out5 = handler->PatternNameHandle({card10,card11,card12,card13,card14});


    EXPECT_EQ(out1,"葫蘆");
    EXPECT_EQ(out2,"順子");
    EXPECT_EQ(out5,"順子");


    EXPECT_NE(out3,"葫蘆");
    EXPECT_NE(out4,"葫蘆");
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

