#ifndef _SAMETYPEHANDLER_H_
#define _SAMETYPEHANDLER_H_

#include "../include/CollisionHandle.hpp"
class Sprite;

class SameTypeHandler:public CollisionHandle
{
private:
    /* data */
public:
    SameTypeHandler(CollisionHandle* next);
    ~SameTypeHandler();

    bool match(Sprite* c1,Sprite* c2) override;
    void dohandle(Sprite* c1,Sprite* c2) override;
};




#endif /* _SAMETYPEHANDLER_H_ */
