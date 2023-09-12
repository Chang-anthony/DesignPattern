#include "../include/Marry.hpp"
#include "../include/Love.hpp"

Marry::Marry()
{

}

Marry::Marry(Love* inlove,int day):inlove(inlove),day(day)
{

}

void Marry::Divorce(int day)
{
    if(day != this->day)
    {
        std::cout << "this marry is broken!!!" << std::endl;
        this->inlove->SetMarry(nullptr);
        this->inlove->breakup();
    } 
    else
        std::cout << "this marry is happy!!!" << std::endl;
}

Marry::~Marry()
{

}