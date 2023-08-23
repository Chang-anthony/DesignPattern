#include "../include/Love.hpp"
#include "../include/Marry.hpp"
#include "../include/Preson.hpp"

Love::Love(Preson* p1,Preson* p2):p1(p1),p2(p2)
{

}

Marry* Love::Domarry()
{
    std::cout << "two preson marry!!!" << std::endl; 
    Marry* marry = new Marry(this);
    this->SetMarry(marry);
    
    return marry;
}

void Love::SetMarry(Marry* marry)
{
    this->marry = marry;
}

void Love::breakup()
{
    this->p1->SetInLove(nullptr);
    this->p2->SetInLove(nullptr);
}

Love::~Love()
{
}