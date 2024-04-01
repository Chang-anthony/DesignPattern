#include <Role.hpp>
#include <NormalState.hpp>
#include <Invincible.hpp>
#include <Adventure.hpp>
#include <Teleport.hpp>
#include <Coord.hpp>

//TODO adventure teleport method
Teleport::Teleport(Role* role) : State(role)
{
}

void Teleport::enterState()
{
    return;
}

void Teleport::exitState(State* nextState)
{
    role->EnterState(nextState);
}

void Teleport::action()
{
    role->Do();
    round++;
    if(round > 1) {
        Adventure* game = role->GetGame();
        Coord* newPos = Coord::RandomCoord(game->GetBoundX(), game->GetBoundY());
        while (true) {
            if(game->IsNullObj(newPos))
                break;
            else
                newPos = Coord::RandomCoord(game->GetBoundX(), game->GetBoundY());
        }
        role->SetCoord(newPos);
        exitState(new NormalState(role));
    }
}

void Teleport::attacked(int damage)
{
    role->lossHp(damage);
    //to 無敵狀態
    if(!role->isDead())
        exitState(new Invincible(role));
}

std::string Teleport::StateName()
{
    return "瞬身";
}

Teleport::~Teleport()
{
}