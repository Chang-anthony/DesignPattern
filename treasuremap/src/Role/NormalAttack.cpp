#include <NormalAttack.hpp>
#include <Adventure.hpp>
#include <Role.hpp>

NormalAttack::NormalAttack(Role* role) : AttackType(role)
{
    SetDamage(999);
}

//TODO
void NormalAttack::attack()
{
}

NormalAttack::~NormalAttack()
{
}