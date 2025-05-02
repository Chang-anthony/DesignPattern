#include "CheerupHandler.hpp"

CheerupHandler::CheerupHandler() {}

CheerupHandler::CheerupHandler(OnePunchHandler* nextHandler)
    : OnePunchHandler(nextHandler) {}

CheerupHandler::~CheerupHandler() {}

bool CheerupHandler::match() const {
    // Logic to determine if this handler should handle the request
    std::cout << "CheerupHandler: Checking if it matches..." << std::endl;
    return true; // Default to true for demonstration purposes
}

void CheerupHandler::doHandle() {
    // Logic to handle the request
    std::cout << "CheerupHandler: Handling the cheer-up state." << std::endl;
}
