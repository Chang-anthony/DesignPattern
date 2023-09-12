#include "../include/Preson.hpp"
#include "../include/Love.hpp"

Preson::Preson(/* args */)
{
    this->inlove = nullptr;
}

Love* Preson::InLove(Preson* preson)
{
    if(this->inlove != nullptr)
    {
        throw std::invalid_argument("you only can love one preson");
    }
    std::cout << "this preson in love anthoer preson" << std::endl;
    Love* inlove = new Love(this,preson);
    this->inlove = inlove;
    return inlove;
}

void Preson::SetInLove(Preson* love)
{
    this->inlove = nullptr;
}

Preson::~Preson()
{

}
