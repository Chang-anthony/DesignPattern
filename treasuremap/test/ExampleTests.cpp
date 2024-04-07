#include <iostream>
#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <NormalState.hpp>
#include <NormalAttack.hpp>
#include <Role.hpp>
#include <Adventure.hpp>
#include <Invincible.hpp>
#include <Teleport.hpp>
#include <Orderless.hpp>
#include <Poisoned.hpp>
#include <Stockpile.hpp>
#include <Erupting.hpp>
#include <Accelerated.hpp>
#include <Monster.hpp>
#include <Charator.hpp>
#include <Coord.hpp>
#include <Healing.hpp>


TEST(Poisoned, Poisoned_TEST)
{
    Adventure* game = new Adventure();
    Charator* main = new Charator(new Coord(0, 0), game);
    game->SetCharator(main);
    game = Adventure::newGame();
    
    main->EnterState(new Poisoned(main));
    main->test();
    main->test();
    main->test();
    EXPECT_EQ(main->GetHp(), 300-15*3);
    EXPECT_EQ(main->GetState()->StateName(), "正常");
}

TEST(Invincible, Invincible_TEST)
{
    Adventure* game = new Adventure();
    Charator* main = new Charator(new Coord(0, 0), game);
    game->SetCharator(main);
    game = Adventure::newGame();
    
    main->EnterState(new Invincible(main));
    main->injured(15);
    EXPECT_EQ(main->GetHp(), 300);
    main->test();
    main->injured(15);
    EXPECT_EQ(main->GetHp(), 300);
    main->test();
    EXPECT_EQ(main->GetState()->StateName(), "正常");
    main->injured(15);
    EXPECT_EQ(main->GetHp(), 285);
    main->test();
    EXPECT_EQ(main->GetState()->StateName(), "無敵");
}

TEST(Accelerated, Accelerated_TEST)
{
    Adventure* game = new Adventure();
    Charator* main = new Charator(new Coord(0, 0), game);
    game->SetCharator(main);
    game = Adventure::newGame();
    
    main->EnterState(new Accelerated(main));
    EXPECT_EQ(main->GetState()->StateName(), "加速");
    main->injured(15);
    EXPECT_EQ(main->GetState()->StateName(), "正常");
    main->EnterState(new Accelerated(main));
    main->test();
    main->test();
    main->test();
    EXPECT_EQ(main->GetState()->StateName(), "正常");
}

TEST(Healing, Healing_TEST)
{
    Adventure* game = new Adventure();
    Charator* main = new Charator(new Coord(0, 0), game);
    game->SetCharator(main);
    game = Adventure::newGame();
    main->SetHp(100);
    
    main->EnterState(new Healing(main));
    EXPECT_EQ(main->GetState()->StateName(), "回復");
    main->test();
    main->test();
    main->test();
    main->test();
    main->test();
    EXPECT_EQ(main->GetHp(), 250);
    EXPECT_EQ(main->GetState()->StateName(), "正常");
    main->EnterState(new Healing(main));
    main->injured(50);
    EXPECT_EQ(main->GetHp(), 200);
    EXPECT_EQ(main->GetState()->StateName(), "無敵");
}

TEST(Teleport, Teleport_TEST)
{
    Adventure* game = new Adventure();
    Charator* main = new Charator(new Coord(0, 0), game);
    game->SetCharator(main);
    game = Adventure::newGame();

    Coord* now = main->GetCoord();
    
    main->EnterState(new Teleport(main));
    EXPECT_EQ(main->GetState()->StateName(), "瞬身");
    main->test();
    Coord* newp = main->GetCoord();
    EXPECT_NE(now, newp);
    EXPECT_EQ(main->GetState()->StateName(), "正常");
    main->EnterState(new Teleport(main));
    main->injured(50);
    EXPECT_EQ(main->GetState()->StateName(), "無敵");
}

TEST(Orderless, Orderless_TEST)
{
    Adventure* game = new Adventure();
    Charator* main = new Charator(new Coord(0, 0), game);
    game->SetCharator(main);
    game = Adventure::newGame();

    Coord* now = main->GetCoord();
    
    main->EnterState(new Orderless(main));
    EXPECT_EQ(main->GetState()->StateName(), "混亂");
    main->test();
    main->test();
    main->test();
    EXPECT_EQ(main->GetState()->StateName(), "正常");

    main->EnterState(new Orderless(main));
    main->injured(50);
    EXPECT_EQ(main->GetState()->StateName(), "無敵");
}

TEST(Stockpile, Stockpile_TEST)
{
    Adventure* game = new Adventure();
    Charator* main = new Charator(new Coord(0, 0), game);
    game->SetCharator(main);
    game = Adventure::newGame();

    Coord* now = main->GetCoord();
    
    main->EnterState(new Stockpile(main));
    EXPECT_EQ(main->GetState()->StateName(), "蓄力");
    main->test();
    main->test();
    EXPECT_EQ(main->GetState()->StateName(), "爆發");
    
    main->EnterState(new Stockpile(main));
    main->injured(50);
    EXPECT_EQ(main->GetState()->StateName(), "正常");
}

TEST(Erupting, Erupting_TEST)
{
    Adventure* game = new Adventure();
    Charator* main = new Charator(new Coord(0, 0), game);
    game->SetCharator(main);
    game = Adventure::newGame();

    Coord* now = main->GetCoord();
    
    main->EnterState(new Erupting(main));
    EXPECT_EQ(main->GetState()->StateName(), "爆發");
    main->test();
    EXPECT_EQ(main->GetAttackType()->GetDamage(), 50);
    EXPECT_EQ(main->GetGame()->isEnd(), true);
    main->test();
    main->test();
    EXPECT_EQ(main->GetState()->StateName(), "瞬身");

    main->EnterState(new Erupting(main));
    main->injured(50);
    EXPECT_EQ(main->GetState()->StateName(), "無敵");
}

TEST(Adventure, Adventure_TEST)
{
    Adventure* game = new Adventure();
    Charator* main = new Charator(new Coord(0, 0), game);
    game->SetCharator(main);
    game = Adventure::newGame();

    std::vector<Mapobject*> mons = game->GetSymbolObjs("M");
    std::vector<Mapobject*> obsts = game->GetSymbolObjs("o");
    std::vector<Mapobject*> treas = game->GetSymbolObjs("X");

    EXPECT_EQ(mons.size(), 5);
    EXPECT_EQ(obsts.size(), 5);
    EXPECT_EQ(treas.size(), 5);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}

