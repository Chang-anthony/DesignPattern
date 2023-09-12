#include "../include/Classmate.hpp"

Classmate::Classmate(/* args */)
{
    this->friends = std::set<Classmate*>();
}

void Classmate::makefriend(Classmate* classmate)
{
    std::cout << "make new friend!!!" <<std::endl;
    //雙向關聯
    this->friends.insert(classmate);
    classmate->friends.insert(this);
}

Classmate::~Classmate()
{
}