#include <Content.hpp>
#include <Treasure.hpp>
#include <Coord.hpp>
#include <Adventure.hpp>
#include <Role.hpp>
#include <State.hpp>

Treasure::Treasure(Coord* pos, Adventure* game) : Mapobject("X", pos, game)
{
    this->content = randomContent();
}

void Treasure::open(Role* role)
{   
    State* newState = content2State(role, content);
    role->EnterState(newState);
}

Treasure* Treasure::genTreasure(Coord* newPos, Adventure* game)
{
    return new Treasure(newPos, game);
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

void Treasure::move(int x, int y)
{
    return;
}

Treasure::~Treasure()
{
}