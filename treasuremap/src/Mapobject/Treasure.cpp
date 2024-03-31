#include <Content.hpp>
#include <Treasure.hpp>
#include <Coord.hpp>
#include <Adventure.hpp>

Treasure::Treasure(Coord* pos, Adventure* game) : Mapobject('X', pos, game)
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