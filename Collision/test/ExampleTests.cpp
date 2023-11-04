#include <gtest/gtest.h>
#include "../include/Sprite.hpp"
#include "../include/Fire.hpp"
#include "../include/Water.hpp"
#include "../include/Hero.hpp"
#include "../include/World.hpp"


TEST(Sprite,Sprite_test)
{
    Water* water = new Water();
    Fire* fire = new Fire();
    Hero* hero = new Hero();

    EXPECT_EQ(water->GetType(),'W');
    EXPECT_EQ(fire->GetType(),'F');
    EXPECT_EQ(hero->GetType(),'H');
    EXPECT_EQ(hero->GetHp(),30);
}

TEST(World,World_test)
{
    World* world = new World();

    std::set<int> pos = world->GetPostion();
    std::vector<Sprite*> sprites = world->GetSprites();

    EXPECT_EQ(pos.size(),10);
    EXPECT_EQ(sprites.size(),10);
}