#include "ResetCommand.hpp"
#include "MainController.hpp"
#include "utils.hpp"

ResetCommand::ResetCommand(MainController controller)
{
    utils::RequireNonNull(&controller);
    this->controller = controller;
}

void ResetCommand::execute()
{
    std::map<char, Command*> m = std::map<char, Command*>();
    this->controller.resetCommand();
    // this->controller.setterCommands(m);
    // controller->setterCommands(m);
    // this->controller->resetCommand();
}

void ResetCommand::undo()
{
    // this->controller->undoresetCommand();
}

ResetCommand::~ResetCommand()
{
}