#include <StandardLayout.hpp>

StandardLayout::StandardLayout(Logger* logger) : Layout(logger)
{
}

//TODO: Implement the format method
std::string StandardLayout::format(std::string message)
{
    return message;
}

StandardLayout::~StandardLayout()
{
}