#ifndef _HEROFIREHANDLER_H_
#define _HEROFIREHANDLER_H_

#include "../include/CollisionHandle.hpp"
class Sprite;

class HeroFireHandler : public CollisionHandle
{
private:
    /* data */
public:
    HeroFireHandler(CollisionHandle* next);
    ~HeroFireHandler();

    bool match(Sprite* c1,Sprite* c2) override;
    void dohandle(Sprite* c1,Sprite* c2) override;
};

#endif /* _HEROFIREHANDLER_H_ */
