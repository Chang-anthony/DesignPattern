#ifndef _RANK_H_
#define _RANK_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <map>

enum class Rank
{
    Sec,
    Thr,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Night,
    Ten,
    J,
    Q,
    K,
    A
};

std::string RankToString(Rank rank);

#endif /* _RANK_H_ */
