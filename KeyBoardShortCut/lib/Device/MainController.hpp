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
    std::map<char, Command*> command;
public:
    MainController(/* args */);
    ~MainController();

    void opeator(char key);
    void resetCommand();
    void undoresetCommand();
    void undo();
    void redo();

    void setCommand(char key, Command* command);
protected:
    std::map<char, Command*> save;
    std::stack<Command*> done;
    std::stack<Command*> s2;
};

#endif /* _MAINCONTROLLER_H_ */
