#include "MainController.hpp"
#include "utils.hpp"
#include "Command.hpp"

MainController::MainController(/* args */)
{
    this->command = std::map<char, Command*>();
    this->done = std::stack<Command*>();
    this->s2 = std::stack<Command*>();
}

void MainController::opeator(char key)
{
    if(this->command.count(key) == 0)
        return;
    std::cout << "map size:" << this->command.size() << std::endl;
    if(this->command.size() > 0 && this->command.find(key) != this->command.end()) {
        this->command[key]->execute();
        this->done.push(this->command[key]);
        this->s2 = std::stack<Command*>();
    }else {
        std::cout << "The controller not have this command." << std::endl;
    }
}

void MainController::setCommand(char key, Command* command)
{
    utils::RequireNonNull(command);
    this->command.insert({key, command});
}

void MainController::resetCommand()
{
    std::map<char, Command*> copy(this->command);
    this->save = copy;
    this->command.clear();
    this->done = std::stack<Command*>();
    this->s2 = std::stack<Command*>();
}

void MainController::undoresetCommand()
{
    std::cout << "Unsuported this operation" << std::endl;
    std::map<char, Command*> copy(this->save);
    this->command = copy;
    this->save.clear();
}

void MainController::undo()
{
    if(!this->done.empty()) {
        Command* last = this->done.top();
        this->done.pop();
        last->undo();
        this->s2.push(last);
    }
    else {
        std::cout << "Not have Command can undo" << std::endl;
    }

}

//做了undo 發現做錯要復原
void MainController::redo()
{
    if(!this->s2.empty()) {
        Command* re = this->s2.top();
        this->s2.pop();
        re->execute();
        this->done.push(re);
    }
    else {
        std::cout << "Not have Command can redo" << std::endl;
    }
}

MainController::~MainController()
{
}