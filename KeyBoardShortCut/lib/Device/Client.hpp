#ifndef _CLIENT_H_
#define _CLIENT_H_


#include <iostream>
#include <vector>
class MainController;
class Tank;
class Telecom;
class Command;

class Client
{
private:
    /* data */
    MainController* contorl;
    Tank* tank;
    Telecom* telecom;

    void setCommand(char key, bool ismarco);
    Command* genCommand(int num);
public:
    Client(MainController* control, Tank* tank, Telecom* telecom);
    ~Client();

    void control();

};

#endif /* _CLIENT_H_ */
