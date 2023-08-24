#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include <iostream>
#include <set>
#include <vector>
#include "../include/Item.hpp"

class Directory : public Item
{
private:
    /* data */
    std::set<Item*> items;
public:
    Directory(/* args */);
    ~Directory();

    void AddItem(Item* item);
    void Delete();
};




#endif /* _DIRECTORY_H_ */
