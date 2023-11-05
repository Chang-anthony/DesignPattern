#include <gtest/gtest.h>
#include "../include/Sprite.hpp"
#include "../include/Fire.hpp"
#include "../include/Water.hpp"
#include "../include/Hero.hpp"
#include "../include/World.hpp"
#include "../include/CollisionHandle.hpp"


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
    // CollisionHandle* head = new CollisionHandle();
    World* world = new World();
    World* world2 = new World();

    Sprite** sprites = world->GetSprites();
    Sprite** gen = world->GenSprites();
    world->SetSprites(gen);
    // Sprite* (*gen2)[30] = world->TestGenSprites();
    
    Sprite** nowSprites = world->GetSprites();

    Sprite* T1 = *(nowSprites+1);
    Sprite* T2 = *(gen+1); 


    EXPECT_EQ(T1,T2);
    //EXPECT_EQ(*(nowSprites+3)->GetCoord(),*(gen+3)->GetCoord());

    Sprite* (*gen2)[30] = world->TestGenSprites();
    world2->SetSprites(gen2);
    Sprite** nowSprites2 = world2->GetSprites();

    Sprite* T3 = *(nowSprites2+2);
    Sprite* T4 = (*gen2)[2];// (*gen2) -> Sprite* [30]

    EXPECT_EQ(T3,T4);

    std::cout << "Test Done" << std::endl;
    // EXPECT_EQ(sprites[1],nullptr);
    // EXPECT_EQ(sprites.size(),10);

}
