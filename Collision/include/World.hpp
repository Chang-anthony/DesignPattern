#ifndef _WORLD_H_
#define _WORLD_H_

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

class Sprite;
class CollisionHandle;

class World
{
private:
    /* data */
    Sprite* sprites[30];
    CollisionHandle* CoR;
public:
    World();
    ~World();
    void AddSprite(Sprite* sprite);
    void Move(int x1,int x2);
    void Collision(Sprite* c1,Sprite* c2);
    Sprite** GenSprites();
    Sprite* (*TestGenSprites())[30];

    //getter
    Sprite** GetSprites();

    //setter
    void SetSprites(Sprite** sprites);
    void SetSprites(Sprite* (*sprites)[30]);
};

#endif /* _WORLD_H_ */
