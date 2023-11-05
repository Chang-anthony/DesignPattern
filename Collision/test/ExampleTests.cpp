#include <gtest/gtest.h>
#include <typeinfo>
#include "../include/Sprite.hpp"
#include "../include/Fire.hpp"
#include "../include/Water.hpp"
#include "../include/Hero.hpp"
#include "../include/World.hpp"
#include "../include/CollisionHandle.hpp"
#include "../include/SameTypeHandler.hpp"
#include "../include/HeroFireHandler.hpp"
#include "../include/HeroWaterHandler.hpp"
#include "../include/WaterFireHandler.hpp"


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
    HeroFireHandler* head = new HeroFireHandler(
                                new HeroWaterHandler(
                                    new WaterFireHandler(
                                        new SameTypeHandler(
                                            nullptr))));
    World* world = new World(head);
    World* world2 = new World(head);

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

TEST(Sprite,Dynamic_cast_TEST)
{
    Sprite* h = new Hero();
    Hero* T = dynamic_cast<Hero*>(h);
    h = dynamic_cast<Hero*>(h);

    
    bool Test = T == nullptr;
    bool Test2 = h == nullptr;

    EXPECT_EQ(Test,false);
    //測試完還是 Sprite 的指標類型只是確認確實是Hero型別
    EXPECT_EQ(Test2,false);
    EXPECT_EQ(T->GetHp(),30);

}

TEST(HeroFireHandler,Collision_TEST_HeroFire)
{
    HeroFireHandler* head = new HeroFireHandler(
                                new HeroWaterHandler(
                                    new WaterFireHandler(
                                        new SameTypeHandler(
                                            nullptr))));
    World* world = new World(head);

    Sprite* h = new Hero();
    Sprite* f1 = new Fire();
    Sprite* f2 = new Fire();
    Sprite* f3 = new Fire();

    h->SetCoord(2);
    f1->SetCoord(3);
    f2->SetCoord(4);
    f3->SetCoord(5);

    world->AddSprite(h);
    world->AddSprite(f1);
    world->AddSprite(f2);
    world->AddSprite(f3);

    world->Move(2,3);
    Hero* T = dynamic_cast<Hero*>(h);
    Sprite** Test = world->GetSprites();
    EXPECT_EQ(Test[2],nullptr); 
    EXPECT_EQ(T->GetHp(),20);

    world->Move(3,4);
    Test = world->GetSprites();
    EXPECT_EQ(Test[3],nullptr); 
    EXPECT_EQ(T->GetHp(),10);

    world->Move(4,5);
    Test = world->GetSprites();
    EXPECT_EQ(Test[4],nullptr); 

    EXPECT_EQ(T->GetHp(),0);
    Test = world->GetSprites();
    EXPECT_EQ(Test[5],nullptr); 
    
}


TEST(HeroWaterHandler,Collision_TEST_HeroWater)
{
    HeroFireHandler* head = new HeroFireHandler(
                                new HeroWaterHandler(
                                    new WaterFireHandler(
                                        new SameTypeHandler(
                                            nullptr))));
    World* world = new World(head);

    Sprite* h = new Hero();
    Sprite* W1 = new Water();
    Sprite* W2 = new Water();
    Sprite* W3 = new Water();

    h->SetCoord(2);
    W1->SetCoord(3);
    W2->SetCoord(4);
    W3->SetCoord(5);

    world->AddSprite(h);
    world->AddSprite(W1);
    world->AddSprite(W2);
    world->AddSprite(W3);

    world->Move(2,3);
    Hero* T = dynamic_cast<Hero*>(h);
    Sprite** Test = world->GetSprites();
    EXPECT_EQ(Test[2],nullptr); 
    EXPECT_EQ(T->GetHp(),40);

    world->Move(3,4);
    Test = world->GetSprites();
    EXPECT_EQ(Test[3],nullptr); 
    EXPECT_EQ(T->GetHp(),50);

    world->Move(4,5);
    Test = world->GetSprites();
    EXPECT_EQ(Test[4],nullptr); 

    EXPECT_EQ(T->GetHp(),60);
    Test = world->GetSprites();
}

TEST(WaterFireHandler,Collision_TEST_WaterFire)
{
    HeroFireHandler* head = new HeroFireHandler(
                                new HeroWaterHandler(
                                    new WaterFireHandler(
                                        new SameTypeHandler(
                                            nullptr))));
    World* world = new World(head);

    Sprite* h = new Hero();
    Sprite* W1 = new Water();
    Sprite* F1 = new Fire();
    Sprite* W3 = new Water();

    h->SetCoord(2);
    W1->SetCoord(3);
    F1->SetCoord(4);
    W3->SetCoord(5);

    world->AddSprite(h);
    world->AddSprite(W1);
    world->AddSprite(F1);
    world->AddSprite(W3);

    world->Move(3,4);
    Hero* T = dynamic_cast<Hero*>(h);
    Sprite** Test = world->GetSprites();
    EXPECT_EQ(Test[3],nullptr);
    EXPECT_EQ(Test[4],nullptr);  

    world->Move(2,5);
    Test = world->GetSprites();
    EXPECT_EQ(Test[2],nullptr); 
    EXPECT_EQ(T->GetHp(),40);

}

TEST(SameTypeHandler,Collision_TEST_SameType)
{
    HeroFireHandler* head = new HeroFireHandler(
                                new HeroWaterHandler(
                                    new WaterFireHandler(
                                        new SameTypeHandler(
                                            nullptr))));
    World* world = new World(head);

    Sprite* h = new Hero();
    Sprite* h1 = new Hero();
    Sprite* F1 = new Fire();
    Sprite* W3 = new Water();

    h->SetCoord(2);
    h1->SetCoord(3);
    F1->SetCoord(4);
    W3->SetCoord(5);

    world->AddSprite(h);
    world->AddSprite(h1);
    world->AddSprite(F1);
    world->AddSprite(W3);

    world->Move(2,3);
    Hero* T = dynamic_cast<Hero*>(h);
    Sprite** Test = world->GetSprites();
    EXPECT_EQ(Test[2],h);
    EXPECT_EQ(Test[3],h1);  

}


