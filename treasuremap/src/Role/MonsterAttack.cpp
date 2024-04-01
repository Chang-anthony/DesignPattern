
#include <MonsterAttack.hpp>
#include <Role.hpp>
#include <Adventure.hpp>

MonsterAttack::MonsterAttack(Role* role) : AttackType(role)
{
    SetDamage(50);
}

//TODO
void MonsterAttack::attack() 
{
    
}

MonsterAttack::~MonsterAttack()
{
}