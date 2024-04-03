
#include <MonsterAttack.hpp>
#include <Role.hpp>
#include <Adventure.hpp>
#include <Charator.hpp>

MonsterAttack::MonsterAttack(Role* role) : AttackType(role)
{
    SetDamage(50);
}

void MonsterAttack::attack() 
{
    Adventure* game = charator->GetGame();
    game->GetCharator()->injured(damage);
}

MonsterAttack::~MonsterAttack()
{
}