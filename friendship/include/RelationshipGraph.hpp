#ifndef _RELATIONSHIPGRAPH_H_
#define _RELATIONSHIPGRAPH_H_

#include <iostream>
#include <vector>
#include <string>


class Relation;
class ConnectivityAnalyerAdapter;

class RelationshipGraph {

public:
    RelationshipGraph();

    virtual bool hasConnection(std::vector<Relation*> graph, const std::string& name1, const std::string& name2) = 0;
    virtual std::vector<std::string> isMutualFriend(std::vector<Relation*> graph, std::string name1, std::string name2) = 0;
    virtual std::vector<Relation*> parser(std::vector<std::string> scripts) = 0;

    ~RelationshipGraph();
private:
    ConnectivityAnalyerAdapter* adapter;
};


#endif /* _RELATIONSHIPGRAPH_H_ */
