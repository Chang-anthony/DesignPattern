#ifndef POISONPETROCHEMICALHANDLER_HPP
#define POISONPETROCHEMICALHANDLER_HPP

#include "OnePunchHandler.hpp"
#include <iostream>

class PoisonPetrochemicalHandler : public OnePunchHandler {
public:
    PoisonPetrochemicalHandler();
    PoisonPetrochemicalHandler(OnePunchHandler* nextHandler);
    ~PoisonPetrochemicalHandler();

    bool match(Role* target) override; // Override match function
    void doHandle(Role* target) override;    // Override doHandle function
};

#endif // POISONPETROCHEMICALHANDLER_HPP
