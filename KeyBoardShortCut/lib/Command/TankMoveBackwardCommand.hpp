#ifndef _TANKMOVEBACKWARDCOMMAND_H_
#define _TANKMOVEBACKWARDCOMMAND_H_

#include <iostream>
#include "Command.hpp"
class Tank;


class TankMoveBackwardCommand: public Command
{
private:
    /* data */
    Tank* tank;
public:
    TankMoveBackwardCommand(Tank* tank);
    ~TankMoveBackwardCommand();

    void execute() override;
    void undo() override;
};



#endif /* _TANKMOVEBACKWARDCOMMAND_H_ */
