#ifndef _WORLD_H_
#define _WORLD_H_

#include <iostream>
#include <vector>
#include <string>
#include <set>

class Sprite;

class World
{
private:
    /* data */
    std::vector<Sprite*> sprites;
public:
    World(/* args */);
    ~World();
    void AddSprites(Sprite* sprite);
    void Move(int x1,int x2);
    void Collision(Sprite* c1,Sprite* c2);

    //getter
    std::vector<Sprite*> GetSprites();
    std::set<int> GetPostion();

    //setter
    void SetSprites(std::vector<Sprite*> sprites);
protected:
    std::set<int> position;
};

#endif /* _WORLD_H_ */
