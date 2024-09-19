#include <Relation.hpp>
#include <RelationshipGraph.hpp>
#include <utils.h>

RelationshipGraph::RelationshipGraph() 
{
    relations = std::vector<Relation*>();
}

RelationshipGraph::RelationshipGraph(std::vector<Relation*> relations) 
{
    SetRelation(relations);
}

//TODO: implement this method
bool RelationshipGraph::hasConnection(const std::string& name1, const std::string& name2) 
{

}

void RelationshipGraph::AddRelation(Relation* relation) {
    utils::RequireNonNull(relation);
    relations.push_back(relation);
}

RelationshipGraph::~RelationshipGraph() {
    for (auto relation : relations) {
        delete relation;
    }
}

std::vector<Relation*> RelationshipGraph::GetRelation() 
{
    return relations;
}

void RelationshipGraph::SetRelation(std::vector<Relation*> relations) 
{
    utils::SizeShouldBigger(relations, 0);
    this->relations = relations;
}