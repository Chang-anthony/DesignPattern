#ifndef _CHEERUPHANDLER_H_
#define _CHEERUPHANDLER_H_

#include "OnePunchHandler.hpp"
#include <iostream>

class CheerupHandler : public OnePunchHandler {
public:
    CheerupHandler();
    CheerupHandler(OnePunchHandler* nextHandler);
    ~CheerupHandler();

    bool match() const override; // Override match function
    void doHandle() override;    // Override doHandle function
};

#endif /* _CHEERUPHANDLER_H_ */
