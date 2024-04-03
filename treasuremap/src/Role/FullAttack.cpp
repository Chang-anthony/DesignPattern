#include <Role.hpp>
#include <Adventure.hpp>
#include <FullAttack.hpp>
#include <Coord.hpp>

FullAttack::FullAttack(Role* role) : AttackType(role)
{
    SetDamage(50);
}

void FullAttack::attack()
{
    std::string dir = charator->GetSymbol();
    std::vector<Role*> attacked = std::vector<Role*>();
    Adventure* game = charator->GetGame();
    std::vector<std::vector<Mapobject*>> objs = game->GetObjs();
    Coord* pos = charator->GetCoord();
    int x = pos->GetX();
    int y = pos->GetY();

    for (int i = 0; i < game->GetBoundX(); i++) {
        for (int j = 0; j < game->GetBoundY(); j++) {
            if(objs[i][j] && objs[i][j]->GetSymbol() == "M")
                attacked.push_back((Role*)objs[i][j]);
        }
    }
    
    for (auto inrange : attacked) {
        inrange->injured(damage);
    }
}

FullAttack::~FullAttack()
{
}