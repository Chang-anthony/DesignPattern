#include <gtest/gtest.h>
#include "../include/Sprite.hpp"
#include "../include/Fire.hpp"
#include "../include/Water.hpp"
#include "../include/Hero.hpp"


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