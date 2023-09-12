#ifndef _CLASSMATE_H_
#define _CLASSMATE_H_

#include <iostream>
#include <set>
#include <vector>

class Classmate
{
private:
    /* data */
    std::set<Classmate*> friends;
public:
    Classmate(/* args */);
    ~Classmate();

    void makefriend(Classmate* classmate);
};

#endif /* _CLASSMATE_H_ */
