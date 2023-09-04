#include <gtest/gtest.h>
#include "../include/Rank.hpp"
#include "../include/Suit.hpp"

TEST(Simple,Test)
{
    EXPECT_EQ(true,true);
}

TEST(Rank,RankTest)
{
    Rank::J;
    EXPECT_EQ("11",RankToString(Rank::J)); 
    EXPECT_EQ("2",RankToString(Rank::Sec)); 
}

TEST(Suit,SuitTest)
{
    Suit a = Suit::Club;

    EXPECT_EQ("1",SuitToString(a)); 
    EXPECT_EQ("1",SuitToString(a)); 
}