#ifndef _COLLISIONHANDLE_H_
#define _COLLISIONHANDLE_H_

class Sprite;

class CollisionHandle
{
protected:
    CollisionHandle* next;
private:
    /* data */
    
public:
    CollisionHandle(/* args */);
    ~CollisionHandle();

    void handle(Sprite* c1,Sprite* c2);
    virtual void match(Sprite* c1,Sprite* c2) = 0;
    virtual void dohandle() = 0;
};

#endif /* _COLLISIONHANDLE_H_ */
