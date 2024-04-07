#ifndef _ROUND_H_
#define _ROUND_H_


#include <iostream>
#include <string>
#include <vector>

class Adventure;
class Round;
class Charator;
class Coord;
class TouchedHandler;
class Role;
class State;

class Round
{
private:
    /* data */
    Adventure* game;
public:
    Round(Adventure* game);
    ~Round();
    void run();

protected:
    void render();
    void operation();
    void gen();
};

#endif /* _ROUND_H_ */
