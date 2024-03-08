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
    Spade,
    None
};

std::string SuitToString(Suit rank);
std::string SuitToName(Suit rank);
Suit CharToSuit(std::string c);
int SuitToNumber(Suit suit);

#endif /* _SUIT_H_ */
