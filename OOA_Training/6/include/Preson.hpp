#ifndef _PRESON_H_
#define _PRESON_H_

#include <iostream>
#include <vector>

class Love;

class Preson
{
private:
    /* data */
    Love* inlove;
public:
    Preson(/* args */);
    ~Preson();
    Love* InLove(Preson* preson);

    //setter
    void SetInLove(Preson* Love);//將他們相愛的人都設為nullptr
};

#endif // _PRESON_H_