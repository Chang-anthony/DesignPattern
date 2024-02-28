#include "MarcoCommand.hpp"
#include "utils.hpp"

MarcoCommand::MarcoCommand(std::vector<Command*> marco)
{
    utils::SizeShouldBigger(marco, 1);
    this->marco = marco;
}

void MarcoCommand::execute()
{
    for(auto command: this->marco)
        command->execute();
}

void MarcoCommand::undo()
{
    for(auto command: this->marco) {
        if(!command)
            printf("NULL");
        command->undo();
    }
}

MarcoCommand::~MarcoCommand()
{
}