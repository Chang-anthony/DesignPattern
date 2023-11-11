#ifndef _NUMBER_H_
#define _NUMBER_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <map>

enum class Number
{
    one,
    Sec,
    Thr,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Night,
    Ten,
};

std::string NumberToString(Number rank);

#endif /* _NUMBER_H_ */
