#include "TelecomdisConnectCommand.hpp"
#include "Telecom.hpp"
#include "utils.hpp"

TelecomdisConnectCommand::TelecomdisConnectCommand(Telecom* telecom)
{
    utils::RequireNonNull(telecom);
    this->telecom = telecom;
}

void TelecomdisConnectCommand::execute()
{
    this->telecom->disconnect();
}

void TelecomdisConnectCommand::undo()
{
    this->telecom->connect();
}

TelecomdisConnectCommand::~TelecomdisConnectCommand()
{
}
