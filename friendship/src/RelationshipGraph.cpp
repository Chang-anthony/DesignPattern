#include <Relation.hpp>
#include <RelationshipGraph.hpp>
#include <utils.h>

RelationshipGraph::RelationshipGraph() {
    relation = nullptr;
}

RelationshipGraph::~RelationshipGraph() {
    delete relation;
}

Relation* RelationshipGraph::GetRelation() {
    return relation;
}

void RelationshipGraph::SetRelation(Relation* relation) {
    utils::RequireNonNull(relation);
    this->relation = relation;
}