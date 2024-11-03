#include <RelationshipAnalyer.hpp>
#include <RelationshipGraph.hpp>
#include <Relation.hpp>
#include <utils.h>

RelationshipAnalyer::RelationshipAnalyer(RelationshipGraph* analyzer)
{
    SetAnalyzer(analyzer);
    graph = std::vector<Relation*>();
}


RelationshipAnalyer::RelationshipAnalyer(std::vector<Relation*> graph, RelationshipGraph* analyzer)
{
    SetAnalyzer(analyzer);
    SetRelation(graph);
}

std::vector<Relation*> RelationshipAnalyer::parser(std::vector<std::string> scripts) 
{
    SetRelation(analyzer->parser(scripts));
    return graph;
}

std::vector<std::string> RelationshipAnalyer::isMutualFriend(std::vector<Relation*> graph, std::string name1, std::string name2) 
{
    return analyzer->isMutualFriend(graph, name1, name2);
}

bool RelationshipAnalyer::hasConnection(std::vector<Relation*> graph, const std::string& name1, const std::string& name2) 
{
    return analyzer->hasConnection(graph, name1, name2);
}

void RelationshipAnalyer::AddRelation(Relation* relation) {
    utils::RequireNonNull(relation);
    graph.push_back(relation);
}


std::vector<Relation*> RelationshipAnalyer::GetRelation() {
    return graph;
}

void RelationshipAnalyer::SetRelation(std::vector<Relation*> relations) {
    utils::SizeShouldBigger(relations, 0);
    this->graph = relations;
}

void RelationshipAnalyer::SetAnalyzer(RelationshipGraph* analyzer) {
    utils::RequireNonNull(analyzer);
    this->analyzer = analyzer;
}

RelationshipAnalyer::~RelationshipAnalyer()
{
    for (auto g : graph) {
        delete g;
    }
    
}

