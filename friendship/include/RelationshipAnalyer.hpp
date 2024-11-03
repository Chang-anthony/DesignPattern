#ifndef _RELATIONSHIPANALYER_H_
#define _RELATIONSHIPANALYER_H_

#include <iostream>
#include <vector>
#include <string>

class Relation;
class RelationshipGraph;

class RelationshipAnalyer
{
private:
    /* data */
    std::vector<Relation*> graph;
public:
    RelationshipAnalyer(RelationshipGraph* analyzer);
    RelationshipAnalyer(std::vector<Relation*> graph, RelationshipGraph* analyzer);

    std::vector<Relation*> parser(std::vector<std::string> scripts);
    std::vector<std::string> isMutualFriend(std::vector<Relation*> graph, std::string name1, std::string name2);
    bool hasConnection(std::vector<Relation*> graph, const std::string& name1, const std::string& name2);
    void AddRelation(Relation* relation);


    //getter
    std::vector<Relation*> GetRelation();
    //setter
    void SetRelation(std::vector<Relation*> relations);
    void SetAnalyzer(RelationshipGraph* analyzer);

    ~RelationshipAnalyer();

protected:
    /* data */

    /* Interface */
    RelationshipGraph* analyzer;
};


#endif /* _RELATIONSHIPANALYER_H_ */
