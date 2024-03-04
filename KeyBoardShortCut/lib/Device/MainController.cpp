#include "MainController.hpp"
#include "utils.hpp"
#include "Command.hpp"
#include <utility>

MainController::MainController(/* args */)
{
    this->command = std::vector<Command*>(26, nullptr);
    this->done = std::stack<Command*>();
    this->s2 = std::stack<Command*>();
}

void MainController::opeator(char key)
{
    if(this->command[key - 'a'] != nullptr) {
        this->command[key - 'a']->execute();
        this->done.push(this->command[key - 'a']);
        this->s2 = std::stack<Command*>();
    }else {
        std::cout << "The controller not have this command." << std::endl;
    }
}

void MainController::setterCommands(std::vector<Command*> command)
{
    this->command = command;
}

void MainController::setCommand(char key, Command* command)
{
    utils::RequireNonNull(command);
    this->command[key - 'a'] = command;
    // this->command.insert({key, command});
}

void MainController::resetCommand()
{   
    std::cout << "Control Reset" << std::endl;
    this->command.clear();
    this->command = std::vector<Command*>(26, nullptr);

    this->done = std::stack<Command*>();
    this->s2 = std::stack<Command*>();
}

void MainController::undoresetCommand()
{
    std::cout << "Unsuported this operation" << std::endl;
}

void MainController::undo()
{
    if(!this->done.empty() && this->done.top() != nullptr) {
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
    if(!this->s2.empty() && this->done.top() != nullptr) {
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