#ifndef _RELATIONSHIPGRAPH_H_
#define _RELATIONSHIPGRAPH_H_

#include <iostream>
#include <vector>
#include <string>

class Relation;

class RelationshipGraph {
public:
    RelationshipGraph();

    virtual bool hasConnection(const std::string& name1, const std::string& name2) = 0;
    
    //getter
    Relation* GetRelation();

    //setter
    void SetRelation(Relation* relation);

    ~RelationshipGraph();
private:
    Relation* relation;
};


#endif /* _RELATIONSHIPGRAPH_H_ */
