/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <csignal>
#include <cstdlib>
#include <vector>
#include "Client.hpp"
#include "MainController.hpp"
#include "ResetCommand.hpp"
#include "Tank.hpp"
#include "Telecom.hpp"

void signalHandler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received.\n";

    // 程序终止
    exit(signum);
}

int main()
{
    signal(SIGINT, signalHandler);

    Tank* tank = new Tank();
    Telecom* telecom = new Telecom();
    MainController* control = new MainController();

    Client* user = new Client(control, tank, telecom);

    // control->setCommand('r', reset);
    
    // control->opeator('r');
    // control->opeator('r');

    while(true)
    {
        user->control();
    }

    return 0;
}