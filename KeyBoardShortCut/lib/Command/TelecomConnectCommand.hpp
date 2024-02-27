#ifndef _TELECOMCONNECTCOMMAND_H_
#define _TELECOMCONNECTCOMMAND_H_

#include <iostream>
#include "Command.hpp"
class Telecom;

class TelecomConnectCommand: public Command
{
private:
    /* data */
    Telecom* telecom;
public:
    TelecomConnectCommand(Telecom* telecom);
    ~TelecomConnectCommand();

    void execute() override;
    void undo() override;
};


#endif /* _TELECOMCONNECTCOMMAND_H_ */
