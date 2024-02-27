#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <iostream>

class Command
{
private:
    /* data */
public:
    Command(/* args */);
    ~Command();

    virtual void execute() = 0;
    virtual void undo() = 0;
};

#endif /* _COMMAND_H_ */
