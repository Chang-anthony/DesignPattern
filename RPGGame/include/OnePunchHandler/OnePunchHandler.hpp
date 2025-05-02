#ifndef ONEPUNCHHANDLER_HPP
#define ONEPUNCHHANDLER_HPP

class OnePunchHandler {
private:
    OnePunchHandler* next; // Pointer to the next handler

public:
    OnePunchHandler();
    OnePunchHandler(OnePunchHandler* nextHandler);
    virtual ~OnePunchHandler();

    void setNext(OnePunchHandler* nextHandler);
    OnePunchHandler* getNext() const;

    void handle(); // Main handler function
    virtual bool match() const; // Function to check if this handler should handle the request
    virtual void doHandle() = 0; // Pure virtual function for handling logic
};

#endif // ONEPUNCHHANDLER_HPP
