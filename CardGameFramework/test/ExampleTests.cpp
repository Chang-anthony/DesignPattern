#include <iostream>
#include <gtest/gtest.h>
#include "gtest/gtest-spi.h"
#include "../include/Rank.hpp"
#include "../include/Suit.hpp"
#include "../include/Card.hpp"
#include "../include/Deck.hpp"
#include "../include/Player.hpp"
#include "../include/HumanPlayer.hpp"
#include "../include/AIPlayer.hpp"

void MyFunction() {
    std::cout << "Hello, World!" << std::endl;
}

// TEST(MyTest, AutomaticInputTest) {

//      // 使用 CaptureStdout 捕获输出
//     testing::internal::CaptureStdout();

//     // 调用需要输出的函数
//     MyFunction();  

//     // 得到輸出函數將其放在test變數
//     std::string test = testing::internal::GetCapturedStdout();

    
//     // 检查输出是否符合预期
//     EXPECT_EQ(test, "Hello, World!\n");
// }

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

TEST(HumanPlayer,PlayerTest)
{
    //pure virtual function can not use this constructor
    HumanPlayer* player1 = new HumanPlayer();
    std::string name = "123";
    Deck* deck = new Deck();
    deck->Suffle();

    // player1->NameSelf();
    // testing::internal::CaptureStdout();

    // std::cout << "123"; 

    // std::string test = testing::internal::GetCapturedStdout();

    EXPECT_EQ("123","123");
    for(int i = 0 ; i < 13;i++)
        player1->DrawCard(deck);

    // EXPECT_EQ(51,deck->GetCards().size());
    // EXPECT_EQ(1,player1->GetHandCards().size());

    // Card* card = player1->GetHandCards()[5];
    // Card* choose = player1->ShowCard();

    // // EXPECT_EQ(card,choose);
    // EXPECT_EQ(12,player1->GetHandCards().size());
    // std::cout << "test" << std::endl;
}

TEST(AIPlayer,PlayerTest)
{
    //pure virtual function can not use this constructor
    AIPlayer* player1 = new AIPlayer();
    std::string name = "456";
    Deck* deck = new Deck();
    deck->Suffle();



    //player1->NameSelf();
    EXPECT_EQ("456","456");
    for(int i = 0 ; i < 13;i++)
        player1->DrawCard(deck);
    int test = 0;

    
    // Card* choose = player1->ShowCard();
    // // std::cin >> test;
    // // Card* card = player1->GetHandCards()[test-1];
    // // EXPECT_EQ(card,choose);
    // EXPECT_EQ(12,player1->GetHandCards().size());
    // std::cout << "test" << std::endl;
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
