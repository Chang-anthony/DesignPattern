#include "RoleObstacleTouched.hpp"
#include "Role.hpp"
#include "Obstacle.hpp"
#include "Mapobject.hpp"
#include <string>

RoleObstacleTouched::RoleObstacleTouched(TouchedHandler* next) : TouchedHandler(next)
{
}

bool RoleObstacleTouched::match(Mapobject* obj1, Mapobject* obj2)
{
    std::string str1 = obj1->GetSymbol();
    bool isCharator = str1 == "↑" || str1 == "→" || str1 == "↓" || str1 == "←";
    
    return (obj1->GetSymbol() == "M" && obj2->GetSymbol() == "o") || (isCharator && obj2->GetSymbol() == "o");
}
void RoleObstacleTouched::dohandle(Mapobject* obj1, Mapobject* obj2)
{
    Do((Role*) obj1, (Obstacle*) obj2);
}

void RoleObstacleTouched::Do(Role* obj1, Obstacle* obj2)
{   
    return;
}

RoleObstacleTouched::~RoleObstacleTouched()
{
}