#include <gtest/gtest.h>
#include "../include/Rank.hpp"
#include "../include/Suit.hpp"
#include "../include/Card.hpp"
#include "../include/Deck.hpp"


TEST(Rank,RankTest)
{
    Rank::J;
    EXPECT_EQ("11",RankToString(Rank::J)); 
    EXPECT_EQ("2",RankToString(Rank::Sec)); 

    EXPECT_EQ("J",RankToName(Rank::J)); 
    EXPECT_EQ("2",RankToName(Rank::Sec));
}

TEST(Suit,SuitTest)
{
    Suit a = Suit::Club;

    EXPECT_EQ("1",SuitToString(a)); 
    EXPECT_EQ("1",SuitToString(a)); 

    EXPECT_EQ("Club",SuitToName(Suit::Club)); 
    EXPECT_EQ("Diamond",SuitToName(Suit::Diamond));
}

TEST(Card,CardTest)
{
    Rank a = Rank::A;
    Suit b = Suit::Club;
    Rank c = Rank::J;
    Card* card =new Card(a,b);
    Card* card2 =new Card(c,b);

    // EXPECT_EQ(card,card2); 
    EXPECT_EQ("11",RankToString(card2->GetRank())); 
}

TEST(Card,CardBiggerTest)
{
    Card* card1 = new Card(Rank::A,Suit::Club);
    Card* card2 = new Card(Rank::A,Suit::Spade);

    Card* card3 = new Card(Rank::J,Suit::Heart);
    Card* card4 = new Card(Rank::Ten,Suit::Diamond);
    
    EXPECT_EQ(false,card1->IsBigger(card2));
    EXPECT_EQ(true,card1->IsBigger(card3));
    EXPECT_EQ(false,card4->IsBigger(card3));
}

TEST(Deck,DeckTest)
{
    Deck* deck = new Deck();
    std::vector<Card*> card1 = deck->GetCards();

    EXPECT_EQ(52,deck->GetCards().size());

    deck->Suffle();
    std::vector<Card*> card2 = deck->GetCards();

    EXPECT_NE(card1[0],card2[1]);
}