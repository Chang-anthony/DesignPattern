#ifndef _CONTENT_H_
#define _CONTENT_H_

#include <iostream>
#include <vector>


class State;

enum Content{
    SuperStar = 0,
    Posion,
    Accelerating,
    Healing,
    Devil,
    KingRock,
    DokoDemoDoor,
};

//TODO : add State
State* content2State(Content* content);
Content randomContent();

#endif /* _CONTENT_H_ */
