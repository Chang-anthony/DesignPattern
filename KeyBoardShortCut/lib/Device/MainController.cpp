#include "MainController.hpp"
#include "utils.hpp"
#include "Command.hpp"

MainController::MainController(/* args */)
{
    this->command = std::map<char, Command*>();
}

void MainController::opeator(char key)
{
    if(this->command.find(key) != this->command.end()) {
        this->command[key]->execute();
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
    this->save = this->command;
    this->command.clear();
}

void MainController::undoresetCommand()
{
    this->command = this->save;
    this->save.clear();
}

void MainController::undo()
{

}

void MainController::redo()
{
    //TODO: redo and undo
}

MainController::~MainController()
{
}