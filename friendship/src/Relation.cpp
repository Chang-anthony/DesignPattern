#include <Relation.hpp>
#include <utils.h>


Relation::Relation(std::string name, Friends* friends)
{
    SetRelations(name, friends);
}

void Relation::SetRelations(std::string name, Friends* friends)
{
    utils::RequireNonNull(friends);
    this->relations.insert({name, friends});
}

std::map<std::string, Friends*> Relation::GetRelations()
{
    return relations;
}

Relation::~Relation()
{
}