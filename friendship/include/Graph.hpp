#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <string>

class RelationshipGraph;

class Graph {
public:
    Graph();
    Graph(const std::vector<std::vector<std::string>>& connects);

    //TODO: implement this method
    std::vector<std::string> isMutualFriend(std::string name1, std::string name2);
    bool hasConnection(const std::string& name1, const std::string& name2);

    const std::vector<std::vector<std::string>>& GetConnections() const;
    void SetConnections(const std::vector<std::vector<std::string>>& connects);

    ~Graph();
private:
    std::vector<std::vector<std::string>> connections;
};

#endif /* _GRAPH_H_ */
