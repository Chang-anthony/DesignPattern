#include "ResetCommand.hpp"
#include "MainController.hpp"
#include "utils.hpp"

ResetCommand::ResetCommand(MainController* controller)
{
    utils::RequireNonNull(controller);
    this->controller = controller;
}

void ResetCommand::execute()
{
    this->controller->resetCommand();
}

void ResetCommand::undo()
{
    this->controller->undoresetCommand();
}

ResetCommand::~ResetCommand()
{
}