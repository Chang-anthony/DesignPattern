#include <TankMoveBackwardCommand.hpp>
#include "Tank.hpp"
#include "utils.hpp"

TankMoveBackwardCommand::TankMoveBackwardCommand(Tank* tank)
{
    utils::RequireNonNull(tank);
    this->tank = tank;
}

void TankMoveBackwardCommand::execute()
{
    this->tank->moveBackward();
}

void TankMoveBackwardCommand::undo()
{
    this->tank->moveForward();
}

TankMoveBackwardCommand::~TankMoveBackwardCommand()
{
}
