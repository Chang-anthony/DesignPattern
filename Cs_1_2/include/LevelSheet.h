#pragma once
#ifndef _LEVELSHEET_H_
#define _LEVELSHEET_H_

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



#endif