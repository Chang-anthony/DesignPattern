#include "PoisonPetrochemicalHandler.hpp"

PoisonPetrochemicalHandler::PoisonPetrochemicalHandler() {}

PoisonPetrochemicalHandler::PoisonPetrochemicalHandler(OnePunchHandler* nextHandler)
    : OnePunchHandler(nextHandler) {}

PoisonPetrochemicalHandler::~PoisonPetrochemicalHandler() {}

bool PoisonPetrochemicalHandler::match() const {
    // Logic to determine if this handler should handle the request
    std::cout << "PoisonPetrochemicalHandler: Checking if it matches..." << std::endl;
    return true; // Default to true for demonstration purposes
}

void PoisonPetrochemicalHandler::doHandle() {
    // Logic to handle the request
    std::cout << "PoisonPetrochemicalHandler: Handling the poison or petrochemical state." << std::endl;
}
