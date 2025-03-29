#include <Level.hpp>

std::map<std::string, Level> stringToLevel = {
    {"TRACE", TRACE},
    {"DEBUG", DEBUG},
    {"INFO", INFO},
    {"WARN", WARN},
    {"ERROR", ERROR},
};

std::map<Level, std::string> levelToString = {
    {TRACE, "TRACE"},
    {DEBUG, "DEBUG"},
    {INFO, "INFO"},
    {WARN, "WARN"},
    {ERROR, "ERROR"},
};