#include "../include/Marry.hpp"
#include "../include/Love.hpp"

Marry::Marry()
{

}

Marry::Marry(Love* inlove):inlove(inlove)
{
    this->day = 10;
}

void Marry::Divorce(int day)
{
    if(day != this->day)
    {
        std::cout << "this marry is broken!!!" << std::endl;
        this->inlove->SetMarry(nullptr);
    } 
    else
        std::cout << "this marry is happy!!!" << std::endl;
}

Marry::~Marry()
{

}