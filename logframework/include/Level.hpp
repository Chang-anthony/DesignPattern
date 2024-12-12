#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <iostream>
#include <string>
#include <map>

enum Level {
    TRACE = 0,
    INFO = 1,
    DEBUG = 2,
    WARN = 3,
    ERROR = 4,
};

extern std::map<std::string, Level> stringToLevel;
extern std::map<Level, std::string> levelToString;

#endif /* _LEVEL_H_ */
