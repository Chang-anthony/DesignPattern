#ifndef _MARRY_H_
#define _MARRY_H_

#include <iostream>

class Love;

class Marry
{
private:
    /* data */
    int day;
    Love* inlove;
public:
    Marry();
    Marry(Love* inlove);
    ~Marry();

    void Divorce(int day);
};

#endif // _MARRY_H_