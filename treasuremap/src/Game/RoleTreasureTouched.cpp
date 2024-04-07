#include <Mapobject.hpp>
#include <RoleTreasureTouched.hpp>
#include <Role.hpp>
#include <Treasure.hpp>
#include <Adventure.hpp>

RoleTreasureTouched::RoleTreasureTouched(TouchedHandler* next, Adventure* game) : TouchedHandler(next, game)
{
}

bool RoleTreasureTouched::match(Mapobject* obj1, Mapobject* obj2)
{
    std::string str1 = obj1->GetSymbol();
    bool isCharator = str1 == "↑" || str1 == "→" || str1 == "↓" || str1 == "←" || str1 == "M";
    
    return (isCharator && obj2->GetSymbol() == "X");
}

void RoleTreasureTouched::dohandle(Mapobject* obj1, Mapobject* obj2)
{
    Do((Role*) obj1, (Treasure*) obj2);
}

void RoleTreasureTouched::Do(Role* obj1, Treasure* obj2)
{
    obj2->open(obj1);
    game->remove(obj2);
}

RoleTreasureTouched::~RoleTreasureTouched()
{
}