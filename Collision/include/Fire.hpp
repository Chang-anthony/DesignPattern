#ifndef _FIRE_H_
#define _FIRE_H_


#include "../include/Sprite.hpp"

class Fire : public Sprite
{
private:
    /* data */
public:
    Fire(/* args */);
    ~Fire();
    void Remove() override;
};

#endif /* _FIRE_H_ */
