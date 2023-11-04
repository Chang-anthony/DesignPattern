#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <iostream>
#include <vector>


class Sprite
{
private:
    /* data */
    int coord;
    char type;
public:
    Sprite(char type);
    ~Sprite();
    //TODO : need to virtual function
    void Remove();
    static Sprite* RandGenSprite();

    //getter
    int GetCoord();
    char GetType();

    //setter
    void SetCoord(int coord);
    void SetType(char type);
};

#endif /* _SPRITE_H_ */
