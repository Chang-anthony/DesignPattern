#ifndef _TANKMOVEFORWARDCOMMAND_H_
#define _TANKMOVEFORWARDCOMMAND_H_

#include <iostream>
#include "Command.hpp"
class Tank;

class TankMoveForwardCommand : public Command
{
private:
    /* data */
    Tank* tank;
public:
    TankMoveForwardCommand(Tank* tank);
    ~TankMoveForwardCommand();

    void execute() override;
    void undo() override;
};

#endif /* _TANKMOVEFORWARDCOMMAND_H_ */
