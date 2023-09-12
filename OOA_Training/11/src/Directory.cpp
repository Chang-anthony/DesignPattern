#include "../include/Directory.hpp"


Directory::Directory(/* args */):Item()
{
    this->items = std::set<Item*>();
}

void Directory::AddItem(Item* item)
{
    this->items.insert(item);
}

void Directory::Delete()
{
    this->items = std::set<Item*>();
}
    
Directory::~Directory()
{
}