#ifndef _JOURNEY_H_
#define _JOURNEY_H_

#include <iostream>
#include <set>
#include <vector>

class Chapter;

class Journey
{
private:
    /* data */
    std::set<Chapter*> chapters;
public:
    Journey(/* args */);
    ~Journey();

    void AddChapter(Chapter* chapter);
};




#endif /* _JOURNEY_H_ */
