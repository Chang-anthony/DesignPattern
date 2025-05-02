#include "NormalHandler.hpp"

NormalHandler::NormalHandler() {}

NormalHandler::NormalHandler(OnePunchHandler* nextHandler) : OnePunchHandler(nextHandler) {}

NormalHandler::~NormalHandler() {}

//TODO:
bool NormalHandler::match() const {
    // Logic to determine if this handler should handle the request
    std::cout << "NormalHandler: Checking if it matches..." << std::endl;
    return true; // Default to true for demonstration purposes
}

void NormalHandler::doHandle() {
    // Logic to handle the request
    std::cout << "NormalHandler: Handling the request." << std::endl;
}
