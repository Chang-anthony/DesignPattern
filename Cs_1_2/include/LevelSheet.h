#include <iostream>
#include <stdio.h>
#include "utils/utils.h"
#include <string>


class LevelSheet
{
private:
    /* data */
public:
    LevelSheet(/* args */);
    ~LevelSheet();

    int queryform(int exp);
};

LevelSheet::LevelSheet(/* args */)
{
}

LevelSheet::~LevelSheet()
{
}

int LevelSheet::queryform(int exp)
{
    return (int) exp/1000;
}

