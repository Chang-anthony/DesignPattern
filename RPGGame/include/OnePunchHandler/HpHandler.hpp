#ifndef HPHANDLER_HPP
#define HPHANDLER_HPP

#include "OnePunchHandler.hpp"
#include <iostream>

class HpHandler : public OnePunchHandler {
private:

public:
    HpHandler();
    HpHandler(OnePunchHandler* nextHandler);
    ~HpHandler();

    bool match() const override; // Override match function
    void doHandle() override;    // Override doHandle function
};

#endif // HPHANDLER_HPP
