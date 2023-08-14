#include <iostream>
#include <stdio.h>
#include <string>


class LevelSheet
{
private:
    /* data */
public:
    LevelSheet(/* args */);
    ~LevelSheet();

    int queryform(int exp);
    
    static int form(int exp);
};

LevelSheet::LevelSheet(/* args */)
{
}

LevelSheet::~LevelSheet()
{
}

int LevelSheet::queryform(int exp)
{
    return (int)exp/1000;
}

int LevelSheet::form(int exp)
{
    return (int)exp/1000;
}

