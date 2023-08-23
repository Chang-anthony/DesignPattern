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
    void SetInLove(Love* Love);
};

#endif // _PRESON_H_