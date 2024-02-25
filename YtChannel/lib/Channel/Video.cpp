#include <Video.hpp>
#include <utils.hpp>

Video::Video(std::string title, std::string description, int length)
{

}

std::string Video::getTitle()
{
    return this->title;
}

std::string Video::getDescrtiption()
{
    return this->description;
}

int Video::getLength() 
{
    return this->length;
}

void Video::setTitle(std::string title)
{
    this->title = title;
}

void Video::setDescription(std::string description)
{
    this->description = description;
}

void Video::setLength(int length)
{

    this->length = length;
}

Video::~Video()
{

}
