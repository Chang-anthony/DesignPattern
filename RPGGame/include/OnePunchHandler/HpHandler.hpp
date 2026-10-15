#ifndef HPHANDLER_HPP
#define HPHANDLER_HPP

#include "OnePunchHandler.hpp"
#include <iostream>

class HpHandler : public OnePunchHandler {
private:

public:
    HpHandler();
    ~HpHandler();

    bool match(Role* actor, Role* target) override; // Override match function
    void doHandle(Role* actor, Role* target) override;    // Override doHandle function
};

#endif // HPHANDLER_HPP
