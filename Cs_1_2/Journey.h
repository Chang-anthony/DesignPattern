#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

class Journey
{
private:
    std::string name;
    std::string description;
    int price; 
public:
    Journey(std::string name,std::string description,int price)
        {
            this->SetName(name);
            this->SetDescription(description);
            this->SetPrice(price);
        }
    ~Journey();


    //getter
    std::string GetName();
    std::string GetDescription();
    int GetPrice();

    //setter
    void SetName(std::string name);
    void SetDescription(std::string description);
    void SetPrice(int price);
};

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

void Journey::SetName(std::string name)
{
    lengthshouldBe(name,1,30);
}

