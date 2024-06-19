#ifndef _RELATION_H_
#define _RELATION_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>


class Friends;

class Relation
{
private:
    /* data */
    std::map<std::string, Friends*> relations;
public:
    Relation(std::string name, Friends* friends);
    ~Relation();

    void SetRelations(std::string name, Friends* friends);
    
    std::map<std::string, Friends*> GetRelations();
};


#endif /* _RELATION_H_ */
