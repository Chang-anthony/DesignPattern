#ifndef _WATERFIREHANDLER_H_
#define _WATERFIREHANDLER_H_

#include "../include/CollisionHandle.hpp"
class Sprite;
class Hero;

class WaterFireHandler:public CollisionHandle
{
private:
    /* data */
public:
    WaterFireHandler(CollisionHandle* next);
    ~WaterFireHandler();

    bool match(Sprite* c1,Sprite* c2) override;
    void dohandle(Sprite* c1,Sprite* c2,Sprite** sprites) override;
};

#endif /* _WATERFIREHANDLER_H_ */
