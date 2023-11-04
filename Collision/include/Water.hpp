#ifndef _WATER_H_
#define _WATER_H_

#include "../include/Sprite.hpp"

class Water : public Sprite
{
private:
    /* data */
public:
    Water(/* args */);
    ~Water();
    void Remove() override;
};

#endif /* _WATER_H_ */
