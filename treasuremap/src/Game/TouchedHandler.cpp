#include <TouchedHandler.hpp>
#include <Mapobject.hpp>
#include <Adventure.hpp>

TouchedHandler::TouchedHandler(TouchedHandler* next, Adventure* game) : next(next), game(game)
{
}

void TouchedHandler::handle(Mapobject* obj1, Mapobject* obj2)
{
    if(this->match(obj1, obj2))
        this->dohandle(obj1, obj2);
    else {
        if(this->next) {
            this->next->handle(obj1, obj2);
        }
    }
}

TouchedHandler::~TouchedHandler()
{
}