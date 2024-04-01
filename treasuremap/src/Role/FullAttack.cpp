#include <Role.hpp>
#include <Adventure.hpp>
#include <FullAttack.hpp>

FullAttack::FullAttack(Role* role) : AttackType(role)
{
    SetDamage(50);
}

//TODO
void FullAttack::attack()
{
}

FullAttack::~FullAttack()
{
}