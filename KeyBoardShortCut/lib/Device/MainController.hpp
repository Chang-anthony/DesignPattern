#ifndef _MAINCONTROLLER_H_
#define _MAINCONTROLLER_H_

#include <iostream>
#include <map>
#include <vector>
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
};

#endif /* _MAINCONTROLLER_H_ */
