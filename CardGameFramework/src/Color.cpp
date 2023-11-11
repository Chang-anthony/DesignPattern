#include "../include/Color.hpp"

std::map<Color,std::string> colorToString =
{
    {Color::Bule,"1"},
    {Color::Red,"2"},
    {Color::Yellow,"3"},
    {Color::Green,"4"},
};

std::map<Color,std::string> colorToName =
{
    {Color::Bule,"Bule"},
    {Color::Red,"Red"},
    {Color::Yellow,"Yellow"},
    {Color::Green,"Green"},
};

std::string ColorToString(Color color)
{
    auto it = colorToString.find(color);
    if(it != colorToString.end())
        return it->second;
    return "0";
}

std::string ColorToName(Color color)
{
    auto it = colorToName.find(color);
    if(it != colorToName.end())
        return it->second;
    return "0";
}