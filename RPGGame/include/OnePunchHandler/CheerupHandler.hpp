#ifndef _CHEERUPHANDLER_H_
#define _CHEERUPHANDLER_H_

#include "OnePunchHandler.hpp"
#include <iostream>

class CheerupHandler : public OnePunchHandler {
public:
    CheerupHandler();
    ~CheerupHandler();

    bool match(Role* actor, Role* target) override; // Override match function
    void doHandle(Role* actor, Role* target) override;    // Override doHandle function
};

#endif /* _CHEERUPHANDLER_H_ */
