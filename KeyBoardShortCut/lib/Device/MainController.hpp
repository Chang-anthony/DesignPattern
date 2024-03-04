#ifndef _MAINCONTROLLER_H_
#define _MAINCONTROLLER_H_

#include <iostream>
#include <map>
#include <vector>
#include <stack>
class Command;

class MainController
{
private:
    /* data */
    std::vector<Command*> command;
public:
    MainController(/* args */);
    ~MainController();

    void opeator(char key);
    void resetCommand();
    void undoresetCommand();

    void undo();
    void redo();

    void setterCommands(std::vector<Command*> command);

    void setCommand(char key, Command* command);
protected:
    std::stack<Command*> done;
    std::stack<Command*> s2;
};

#endif /* _MAINCONTROLLER_H_ */
