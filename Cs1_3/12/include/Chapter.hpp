#ifndef _CHAPTER_H_
#define _CHAPTER_H_

#include <iostream>
#include <set>
#include <vector>

class Mission;

class Chapter
{
private:
    /* data */
    std::set<Mission*> missions;
public:
    Chapter(/* args */);
    ~Chapter();

    void AddMission(Mission* mission);
};

#endif /* _CHAPTER_H_ */
