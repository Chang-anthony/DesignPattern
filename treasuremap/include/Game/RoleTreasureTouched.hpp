#ifndef _ROLETREASURETOUCHED_H_
#define _ROLETREASURETOUCHED_H_

#include <iostream>
#include "TouchedHandler.hpp"

class Mapobject;
class Role;
class Treasure;

class RoleTreasureTouched : public TouchedHandler
{
private:
    /* data */
public:
    RoleTreasureTouched(TouchedHandler* next);
    ~RoleTreasureTouched();

    bool match(Mapobject* obj1, Mapobject* obj2) override;
    void dohandle(Mapobject* obj1, Mapobject* obj2) override;
    void Do(Role* obj1, Treasure* obj2);
};

#endif /* _ROLETREASURETOUCHED_H_ */
