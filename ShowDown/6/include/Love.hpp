#ifndef _LOVE_H_
#define _LOVE_H_

#include <iostream>

class Preson;
class Marry;

class Love
{
private:
    /* data */
    Preson* p1;
    Preson* p2;
    Marry* marry;
public:
    Love(Preson* p1,Preson* p2);
    ~Love();
    Marry* Domarry();

    void breakup();

    //setter
    void SetMarry(Marry* marry);


};

#endif // _LOVE_H_