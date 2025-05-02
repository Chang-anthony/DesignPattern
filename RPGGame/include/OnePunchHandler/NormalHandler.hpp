#ifndef NORMALHANDLER_HPP
#define NORMALHANDLER_HPP

#include "OnePunchHandler.hpp"
#include <iostream>

class NormalHandler : public OnePunchHandler {
public:
    NormalHandler();
    NormalHandler(OnePunchHandler* nextHandler);
    ~NormalHandler();

    bool match() const override; // Override match function
    void doHandle() override;    // Override doHandle function
};

#endif // NORMALHANDLER_HPP
