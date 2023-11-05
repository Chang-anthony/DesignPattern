/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
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


int main()
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
    Sprite* W3 = new Water();

    h->SetCoord(2);
    f1->SetCoord(3);
    f2->SetCoord(4);
    W3->SetCoord(5);

    world->AddSprite(h);
    world->AddSprite(f1);
    world->AddSprite(f2);
    world->AddSprite(W3);

    world->Move(2,3);
    Hero* T = dynamic_cast<Hero*>(h);
    Sprite** Test = world->GetSprites();

    world->Move(3,4);
    Test = world->GetSprites();

    world->Move(4,5);
    Test = world->GetSprites();

    std::cout << " Desired : 1 :"<< !Test[4] << std::endl;

    Hero* H2 = dynamic_cast<Hero*>(Test[5]);
        
    std::cout << "Desired : 10 :" << H2->GetHp() << std::endl;


    return 0;
}