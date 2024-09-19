#ifndef _RELATIONSHIPGRAPH_H_
#define _RELATIONSHIPGRAPH_H_

#include <iostream>
#include <vector>
#include <string>

class Relation;

class RelationshipGraph {

public:
    RelationshipGraph();
    RelationshipGraph(std::vector<Relation*> relations);

    bool hasConnection(const std::string& name1, const std::string& name2);
    void AddRelation(Relation* relation);

    //getter
    std::vector<Relation*> GetRelation();
    //setter
    void SetRelation(std::vector<Relation*> relations);

    ~RelationshipGraph();
private:
    std::vector<Relation*> relations;
};


#endif /* _RELATIONSHIPGRAPH_H_ */
