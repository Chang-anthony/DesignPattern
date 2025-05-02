#ifndef ONEPUNCHHANDLER_HPP
#define ONEPUNCHHANDLER_HPP

#include <iostream>
#include <vector>

class Role;

class OnePunchHandler {
private:
    OnePunchHandler* next; // Pointer to the next handler

public:
    OnePunchHandler();
    OnePunchHandler(OnePunchHandler* nextHandler);
    virtual ~OnePunchHandler();

    void setNext(OnePunchHandler* nextHandler);
    OnePunchHandler* getNext() const;

    void handle(Role* target); // Main handler function
    virtual bool match(Role* target) = 0; // Function to check if this handler should handle the request
    virtual void doHandle(Role* target) = 0; // Pure virtual function for handling logic
};

#endif // ONEPUNCHHANDLER_HPP
