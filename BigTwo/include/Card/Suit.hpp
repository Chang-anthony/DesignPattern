#ifndef _SUIT_H_
#define _SUIT_H_

#include <iostream>
#include <stdio.h>
#include <map>
#include <string>
#include <vector>

enum class Suit
{
    Club,
    Diamond,
    Heart,
    Spade
};

std::string SuitToString(Suit rank);
std::string SuitToName(Suit rank);
int SuitToNumber(Suit suit);

#endif /* _SUIT_H_ */
