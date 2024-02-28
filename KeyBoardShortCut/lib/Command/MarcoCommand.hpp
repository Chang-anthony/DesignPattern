#ifndef _MARCOCOMMAND_H_
#define _MARCOCOMMAND_H_

#include <iostream>
#include <vector>
#include "Command.hpp"


class MarcoCommand : public Command
{
private:
    /* data */
    std::vector<Command*> marco;
public:
    MarcoCommand(std::vector<Command*> marco);
    ~MarcoCommand();

    void execute() override;
    void undo() override;
};

#endif /* _MARCOCOMMAND_H_ */
