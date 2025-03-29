#ifndef _CONNECTIVITYANALYERADAPTER_H_
#define _CONNECTIVITYANALYERADAPTER_H_

#include <iostream>
#include <vector>
#include <RelationshipGraph.hpp>

class Relation;
class Graph;

class ConnectivityAnalyerAdapter : public RelationshipGraph
{
private:
    /* data */
public:
    ConnectivityAnalyerAdapter();
    ~ConnectivityAnalyerAdapter();

    //TODO: implement this method
    std::vector<Relation*> parser(std::vector<std::string> scripts) override;
    bool hasConnection(std::vector<Relation*> graph, const std::string& name1, const std::string& name2) override;
    std::vector<std::string> isMutualFriend(std::vector<Relation*> graph, std::string name1, std::string name2) override;

protected:
    std::string Trim(const std::string& str);
    std::pair<std::string, std::vector<std::string>> parseLine(std::string line);
    std::vector<std::vector<std::string>> ToConnections(std::vector<Relation*> graph);

    Graph* libary;
};


#endif /* _CONNECTIVITYANALYERADAPTER_H_ */
