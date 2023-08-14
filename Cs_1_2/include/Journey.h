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
            :name(name),description(description),price(price){};
    ~Journey();


    //getter

    //setter
};

