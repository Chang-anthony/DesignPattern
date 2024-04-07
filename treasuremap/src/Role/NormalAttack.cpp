#include <NormalAttack.hpp>
#include <Adventure.hpp>
#include <Role.hpp>
#include <Coord.hpp>
#include <stack>

NormalAttack::NormalAttack(Role* role) : AttackType(role)
{
    SetDamage(999);
}

//TODO Can use template method
void NormalAttack::attack()
{
    std::string dir = charator->GetSymbol();
    std::stack<Role*> attacked = std::stack<Role*>();
    Adventure* game = charator->GetGame();
    std::vector<std::vector<Mapobject*>> objs = game->GetObjs();
    Coord* pos = charator->GetCoord();
    int x = pos->GetX();
    int y = pos->GetY();

    if(dir == "↑") {
        //x now work y move
        for (int j = x; j >= 0; j--) {
            if(objs[j][y] && objs[j][y]->GetSymbol() == "o")
                break;
            if(objs[j][y] && objs[j][y]->GetSymbol() == "M")
                attacked.push((Role*)objs[j][y]);
        }
    }
    if(dir == "→") {
        //x now work y move
        for (int j = y; j < game->GetBoundY(); j++) {
            if(objs[x][j] && objs[x][j]->GetSymbol() == "o")
                break;
            if(objs[x][j] && objs[x][j]->GetSymbol() == "M")
                attacked.push((Role*)objs[x][j]);
        }
    }
    if(dir == "↓") {
        //x now work y move
        for (int j = x; j < game->GetBoundX(); j++) {
            if(objs[j][y] && objs[j][y]->GetSymbol() == "o")
                break;
            if(objs[j][y] && objs[j][y]->GetSymbol() == "M")
                attacked.push((Role*)objs[j][y]);
        }
    }
    if(dir == "←") {
        for (int j = y; j >= 0; j--) {
        if(objs[x][j] && objs[x][j]->GetSymbol() == "o")
                break;
            if(objs[x][j] && objs[x][j]->GetSymbol() == "M")
                attacked.push((Role*)objs[x][j]);
        }
    }

    while(!attacked.empty()) {
        Role* inrange = attacked.top();
        attacked.pop();
        inrange->injured(damage);
    }
}

NormalAttack::~NormalAttack()
{
}