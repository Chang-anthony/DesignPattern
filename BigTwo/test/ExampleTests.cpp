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





int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

