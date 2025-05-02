#include "HpHandler.hpp"

HpHandler::HpHandler(){}

HpHandler::HpHandler(OnePunchHandler* nextHandler)
    : OnePunchHandler(nextHandler) { }

HpHandler::~HpHandler() {}

bool HpHandler::match() const {
    // Logic to determine if this handler should handle the request
    std::cout << "HpHandler: Checking if HP is below threshold " << std::endl;
    // Replace with actual logic to check HP
    return true; // Default to true for demonstration purposes
}

void HpHandler::doHandle() {
    // Logic to handle the request
    std::cout << "HpHandler: Handling the request based on HP threshold." << std::endl;
}
