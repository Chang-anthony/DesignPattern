#ifndef _TOUCHEDHANDLER_H_
#define _TOUCHEDHANDLER_H_

#include <iostream>

class Mapobject;
class Adventure;

class TouchedHandler
{
private:
    /* data */
    TouchedHandler* next;
public:
    TouchedHandler(TouchedHandler* next, Adventure* game);
    ~TouchedHandler();
    
    void handle(Mapobject* obj1, Mapobject* obj2); 
    virtual bool match(Mapobject* obj1, Mapobject* obj2) = 0;
    virtual void dohandle(Mapobject* obj1, Mapobject* obj2) = 0;
protected:
    Adventure* game;
};

#endif /* _TOUCHEDHANDLER_H_ */
