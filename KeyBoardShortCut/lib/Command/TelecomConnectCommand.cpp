#include "TelecomConnectCommand.hpp"
#include "Telecom.hpp"
#include "utils.hpp"

TelecomConnectCommand::TelecomConnectCommand(Telecom* telecom)
{
    utils::RequireNonNull(telecom);
    this->telecom = telecom;
}

void TelecomConnectCommand::execute()
{
    this->telecom->connect();
}

void TelecomConnectCommand::undo()
{
    this->telecom->disconnect();
}

TelecomConnectCommand::~TelecomConnectCommand()
{
}