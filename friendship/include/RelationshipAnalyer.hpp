#ifndef _RELATIONSHIPANALYER_H_
#define _RELATIONSHIPANALYER_H_

#include <iostream>
#include <vector>
#include <string>

class RelationshipGraph;

class RelationshipAnalyer
{
private:
    /* data */
    RelationshipGraph* graph;
public:
    RelationshipAnalyer(/* args */);
    ~RelationshipAnalyer();

    virtual RelationshipGraph* parser(std::vector<std::string> scripts);
    virtual std::vector<std::string> isMutualFriend(std::string name1, std::string name2) = 0;
    virtual bool hasConnection(const std::string& name1, const std::string& name2) = 0;

protected:
};


#endif /* _RELATIONSHIPANALYER_H_ */
