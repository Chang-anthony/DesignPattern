#include "TankMoveForwardCommand.hpp"
#include "Tank.hpp"
#include <utils.hpp>


TankMoveForwardCommand::TankMoveForwardCommand(Tank* tank)
{
    utils::RequireNonNull(tank);
    this->tank = tank;
}

void TankMoveForwardCommand::execute()
{
    this->tank->moveForward();
}

void TankMoveForwardCommand::undo()
{
    this->tank->moveBackward();
}

TankMoveForwardCommand::~TankMoveForwardCommand()
{
}