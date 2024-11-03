#include <Graph.hpp>
#include <iostream>
#include <utils.h>
#include <vector>
#include <string>


Graph::Graph()
{
    connections = std::vector<std::vector<std::string>>();
}

Graph::Graph(const std::vector<std::vector<std::string>>& connects)
{
    SetConnections(connects);
}


//TODO: Need to Test this Function
std::vector<std::string> Graph::isMutualFriend(std::string name1, std::string name2)
{
    std::vector<std::string> mutualFriends;

    std::set<std::string> friends1;
    for (int i = 0; i < connections.size(); i++) {
        if (connections[i][0] == name1) {
            for (int j = 1; j < connections[i].size(); j++) {
                friends1.insert(connections[i][j]);
            }
        }
    }

    std::set<std::string> friends2;
    for (int i = 0; i < connections.size(); i++) {
        if (connections[i][0] == name2) {
            for (int j = 1; j < connections[i].size(); j++) {
                friends2.insert(connections[i][j]);
            }
        }
    }
    
    for (std::string friend1 : friends1) {
        if (friends2.find(friend1) != friends2.end()) {
            mutualFriends.push_back(friend1);
        }
    }

    return mutualFriends;
}


//TODO: Need to Test this Function
bool Graph::hasConnection(const std::string& name1, const std::string& name2) 
{
    std::set<std::string> visited;

    return dfs(name1, name2, visited);
}

bool Graph::dfs(const std::string& name1, const std::string& name2, std::set<std::string>& visited) {
    

    for (int i = 0; i < connections.size(); i++) {
        if (connections[i][0] == name1) {
            for (int j = 1; j < connections[i].size(); j++) {
                if (connections[i][j] == name2) {
                    return true;
                }
                if (visited.find(connections[i][j]) == visited.end()) {
                    visited.insert(connections[i][j]);
                    if (dfs(connections[i][j], name2, visited)) {
                        return true;
                    }
                }
            }
        }
    }

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