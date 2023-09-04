#include <gtest/gtest.h>
#include "../include/Rank.hpp"
#include "../include/Suit.hpp"
#include "../include/Card.hpp"


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
    EXPECT_EQ("Club",SuitToName(Suit::Diamond));
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