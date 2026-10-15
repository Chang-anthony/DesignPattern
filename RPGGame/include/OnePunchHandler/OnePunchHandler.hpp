#ifndef ONEPUNCHHANDLER_HPP
#define ONEPUNCHHANDLER_HPP

#include <iostream>
#include <vector>

class Role;

// 鏈改由 OnePunch 以 vector 依序存放，取代 next 指標（D21）；介面帶入 actor（D22）
class OnePunchHandler {
public:
    OnePunchHandler();
    virtual ~OnePunchHandler();

    bool handle(Role* actor, Role* target); // Main handler function：成立時處理並回傳 true
    virtual bool match(Role* actor, Role* target) = 0; // Function to check if this handler should handle the request
    virtual void doHandle(Role* actor, Role* target) = 0; // Pure virtual function for handling logic
};

#endif // ONEPUNCHHANDLER_HPP
