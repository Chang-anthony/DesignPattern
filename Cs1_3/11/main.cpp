/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "../include/Item.hpp"
#include "../include/File.hpp"
#include "../include/Directory.hpp"


int main()
{
    Directory* root = new Directory();

    File* f1 = new File();
    File* f2 = new File();
    Directory* one = new Directory();

    root->AddItem(f1);
    root->AddItem(f2);
    root->AddItem(one);

    root->Delete();
    

    return 0;
}