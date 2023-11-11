#ifndef _COLOR_H_
#define _COLOR_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <map>

enum class Color
{
    Bule,
    Red,
    Yellow,
    Green
};

std::string ColorToString(Color color);
std::string ColorToName(Color rank);

#endif /* _COLOR_H_ */
