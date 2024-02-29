#ifndef _RESETCOMMAND_H_
#define _RESETCOMMAND_H_

#include <iostream>
#include "Command.hpp"
#include "MainController.hpp"

// class MainController;

class ResetCommand : public Command
{
private:
    /* data */
    MainController controller;
public:
    ResetCommand(MainController controller);
    ~ResetCommand();

    void execute() override;
    void undo() override;
};




#endif /* _RESETCOMMAND_H_ */
