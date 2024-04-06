#ifndef _ROLEOBSTACLETOUCHED_H_
#define _ROLEOBSTACLETOUCHED_H_

#include <iostream>
#include "TouchedHandler.hpp"

class Mapobject;
class Role;
class Obstacle;

class RoleObstacleTouched : public TouchedHandler
{
private:
    /* data */
public:
    //TODO
    RoleObstacleTouched(TouchedHandler* next);
    ~RoleObstacleTouched();

    bool match(Mapobject* obj1, Mapobject* obj2) override;
    void dohandle(Mapobject* obj1, Mapobject* obj2) override;
    void Do(Role* obj1, Obstacle* obj2);
};

#endif /* _ROLEOBSTACLETOUCHED_H_ */
