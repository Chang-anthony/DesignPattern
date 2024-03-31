#include <Content.hpp>
#include <Treasure.hpp>
#include <Coord.hpp>

Treasure::Treasure(Coord* pos) : Mapobject('X', pos)
{
    this->content = randomContent();
}

std::string Treasure::NameOfContent()
{
    return this->content2str[this->content];
}

Content Treasure::GetContent()
{
    return this->content;
}

void Treasure::SetContent(Content content)
{
    this->content = content;
}

Treasure::~Treasure()
{
}