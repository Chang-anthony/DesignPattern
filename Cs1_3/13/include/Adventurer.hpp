#ifndef _ADVENTURER_H_
#define _ADVENTURER_H_

class World;

class Adventurer
{
private:
    /* data */
    World* world;
    int step = 0;
public:
    Adventurer(World* world);
    ~Adventurer();

    void RolltheDice();
    void AddStep(int steps);
};

#endif /* _ADVENTURER_H_ */
