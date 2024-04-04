#include <TouchedHandler.hpp>
#include <Mapobject.hpp>

TouchedHandler::TouchedHandler(TouchedHandler* next) : next(next)
{
}

void TouchedHandler::handle(Mapobject* obj1, Mapobject* obj2)
{
    if(this->match(obj1, obj2))
        this->dohandle(obj1, obj2);
    else
        this->next->handle(obj1, obj2);
}

TouchedHandler::~TouchedHandler()
{
}