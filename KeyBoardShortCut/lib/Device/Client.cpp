#include "Client.hpp"
#include "MainController.hpp"
#include "Command.hpp"
#include "Telecom.hpp"
#include "Tank.hpp"
#include "utils.hpp"
#include "TankMoveForwardCommand.hpp"
#include "TankMoveBackwardCommand.hpp"
#include "TelecomConnectCommand.hpp"
#include "TelecomdisConnectCommand.hpp"
#include "ResetCommand.hpp"
#include "MarcoCommand.hpp"
#include <sstream>


Client::Client(MainController* control, Tank* tank, Telecom* telecom)
{
    utils::RequireNonNull(contorl);
    utils::RequireNonNull(tank);
    utils::RequireNonNull(telecom);
    this->contorl = control;
    this->tank = tank;
    this->telecom = telecom;
}

void Client::control()
{
    std::cout << "(1) 快捷鍵設置 (2) Undo (3) Redo (字母) 按下按鍵:" << std::endl;
    int input = utils::HandleInput(1, 3);
    switch (input) {
        case 1: {
            std::cout << "設置巨集指令 (y/n):" << std::endl;
            char input;
            char Key;
            std::cin >> input;
            std::cout << "Key: " << std::endl;
            std::cin >> Key;
            
            if(Key >= 'a' && Key <= 'z')
            {
                if(input == 'y' || input == 'Y')
                    this->setCommand(Key, true);
                else if (input == 'n' || input == 'N')
                    this->setCommand(Key, false);
            }
            else
            {
                std::cout << "This controller unsupport this Key." << std::endl;
            }
        }
        case 2: {
            this->contorl->undo();
        }
        case 3: {
            this->contorl->redo();
        }
        default: {
            break;
        }
    }
}

void Client::setCommand(char key, bool ismarco)
{
    if(ismarco) {
        std::vector<int> inputs = utils::InputMultipleNums();
        std::vector<Command*> marco = std::vector<Command*>();
        for(auto num : inputs) {
            if( num >= 0 && num <= 4) {
                Command* command = this->genCommand(num);
                marco.push_back(command);
            }
            else {
                
                std::cout << "Can't set this marco command please retry." << std::endl;
                return;
            }
        }
        MarcoCommand* marcoCommand = new MarcoCommand(marco);
        this->contorl->setCommand(key, marcoCommand);
    }
    else {
        int input = utils::HandleInput(0, 4);
        Command* command = this->genCommand(input);
        this->contorl->setCommand(key, command);
    }
}

Command* Client::genCommand(int num)
{
    switch (num)
    {
        case 0: {
            return new TankMoveForwardCommand(this->tank);
        }
        case 1: {
            return new TankMoveBackwardCommand(this->tank);
        }
            
        case 2: {
            return new TelecomConnectCommand(this->telecom);
        }
            
        case 3: {
            return new TelecomdisConnectCommand(this->telecom);
        }
        case 4: {
            return new ResetCommand(this->contorl);
        }
        default:
            return nullptr;
    }
}

Client::~Client()
{
}