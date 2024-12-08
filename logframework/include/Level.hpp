#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <iostream>
#include <string>
#include <map>

enum Level {
    TRACE = 0,
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    FATAL = 5,
    OFF = 6
};

std::map<std::string, Level> stringToLevel = {
    {"TRACE", TRACE},
    {"DEBUG", DEBUG},
    {"INFO", INFO},
    {"WARN", WARN},
    {"ERROR", ERROR},
    {"FATAL", FATAL},
    {"OFF", OFF}
};

std::map<Level, std::string> levelToString = {
    {TRACE, "TRACE"},
    {DEBUG, "DEBUG"},
    {INFO, "INFO"},
    {WARN, "WARN"},
    {ERROR, "ERROR"},
    {FATAL, "FATAL"},
    {OFF, "OFF"}
};

#endif /* _LEVEL_H_ */
