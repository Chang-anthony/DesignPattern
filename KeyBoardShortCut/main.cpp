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
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

void signalHandler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received.\n";

    // 程序终止
    exit(signum);
}

int main()
{
#ifdef _WIN32
    // 原始碼是 UTF-8，將 console 輸出改為 UTF-8 才能正確顯示中文
    SetConsoleOutputCP(CP_UTF8);
#endif
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