#ifndef _ROLEOBSTACLETOUCHED_H_
#define _ROLEOBSTACLETOUCHED_H_

#include <iostream>
#include "TouchedHandler.hpp"

class Mapobject;
class Role;

class RoleObstacleTouched : virtual TouchedHandler
{
private:
    /* data */
public:
    //TODO
    RoleObstacleTouched(TouchedHandler* next);
    ~RoleObstacleTouched();

    bool match(Mapobject* obj1, Mapobject* obj2) override;

};

RoleObstacleTouched::RoleObstacleTouched(TouchedHandler* next) : TouchedHandler(next)
{
}

RoleObstacleTouched::~RoleObstacleTouched()
{
}


#endif /* _ROLEOBSTACLETOUCHED_H_ */
