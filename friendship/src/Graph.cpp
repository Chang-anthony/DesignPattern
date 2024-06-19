#include <Graph.hpp>
#include <iostream>
#include <utils.h>


Graph::Graph(const std::vector<std::vector<std::string>>& connects)
{
    SetConnections(connects);
}


//TODO: implement this method
bool Graph::hasConnection(const std::string& name1, const std::string& name2) 
{
    return false;
}

const std::vector<std::vector<std::string>>& Graph::GetConnections() const {
    return connections;
}

void Graph::SetConnections(const std::vector<std::vector<std::string>>& connects) {
    connections = connects;
}


Graph::~Graph()
{
}