#ifndef _CONTENT_H_
#define _CONTENT_H_

#include <iostream>
#include <vector>


class State;
class Role;

enum Content{
    SuperStar = 0,
    Posion,
    Accelerating,
    Heal,
    Devil,
    KingRock,
    DokoDemoDoor,
};

State* content2State(Role* role, Content content);
Content randomContent();

#endif /* _CONTENT_H_ */
