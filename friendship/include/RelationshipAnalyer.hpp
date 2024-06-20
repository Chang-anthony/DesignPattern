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
public:
    RelationshipAnalyer(/* args */);
    ~RelationshipAnalyer();

    RelationshipGraph* parser(std::string script);
    virtual void isMutualFriend(std::string name1, std::string name2) = 0;
};


#endif /* _RELATIONSHIPANALYER_H_ */
