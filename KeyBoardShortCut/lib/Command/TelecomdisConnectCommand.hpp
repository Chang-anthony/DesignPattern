#ifndef _TELECOMDISCONNECTCOMMAND_H_
#define _TELECOMDISCONNECTCOMMAND_H_

#include <iostream>
#include "Command.hpp"
class Telecom;

class TelecomdisConnectCommand : public Command
{
private:
    /* data */
    Telecom* telecom;
public:
    TelecomdisConnectCommand(Telecom* telecom);
    ~TelecomdisConnectCommand();

    void execute() override;
    void undo() override;
};

#endif /* _TELECOMDISCONNECTCOMMAND_H_ */
