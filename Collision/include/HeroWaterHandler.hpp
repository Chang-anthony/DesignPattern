#ifndef _HEROWATERHANDLER_H_
#define _HEROWATERHANDLER_H_

#include "../include/CollisionHandle.hpp"
class Sprite;
class Hero;

class HeroWaterHandler : public CollisionHandle
{
private:
    /* data */
public:
    HeroWaterHandler(CollisionHandle* next);
    ~HeroWaterHandler();

    bool match(Sprite* c1,Sprite* c2) override;
    void dohandle(Sprite* c1,Sprite* c2,Sprite** sprites) override;
};


#endif /* _HEROWATERHANDLER_H_ */
