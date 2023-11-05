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
    CollisionHandle(CollisionHandle* next);
    ~CollisionHandle();

    void handle(Sprite* c1,Sprite* c2);
    virtual bool match(Sprite* c1,Sprite* c2) = 0;
    virtual void dohandle(Sprite* c1,Sprite* c2) = 0;

    //setter
    void SetNext(CollisionHandle* next);
};

#endif /* _COLLISIONHANDLE_H_ */
