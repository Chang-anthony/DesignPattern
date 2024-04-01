#include <AttackType.hpp>
#include <Role.hpp>
#include <utils.h>


AttackType::AttackType(Role* charator)
{
    SetDamage(0);
    SetRole(charator);
}

int AttackType::GetDamage()
{
    return damage;
}

Role* AttackType::GetRole()
{
    return charator;
}
//setter
void AttackType::SetDamage(int damage)
{
    this->damage = damage;
}

void AttackType::SetRole(Role* charator)
{
    this->charator = utils::RequireNonNull(charator);
}

AttackType::~AttackType()
{
}