#include "../include/Journey.h"
#include "../include/Chapter.h"


Journey::Journey(std::string name,std::string description,int price,
        std::vector<Chapter*> chapters)
    {
        this->SetName(name);
        this->SetDescription(description);
        this->SetPrice(price);
        this->SetChapters(chapters);
    }

std::string Journey::GetName()
{
    return this->name;
}

std::string Journey::GetDescription()
{
    return this->description;
}

int Journey::GetPrice()
{
    return this->price;
}

std::vector<Chapter*> Journey::GetChapters()
{
    return this->chapters;
}

void Journey::SetName(std::string name)
{
    utils::LengthShouldBe(name,1,30);
    this->name = name;
}

void Journey::SetDescription(std::string description)
{
    utils::LengthShouldBe(description,0,300);
    this->description = description;
}

void Journey::SetPrice(int price)
{
    utils::ValShouldBigger(price,1);
    this->price = price;
}

void Journey::SetChapters(std::vector<Chapter*> chapter)
{
    utils::SizeShouldBigger(chapter,0);
    this->chapters = chapter;
}

Journey::~Journey()
{
    
}