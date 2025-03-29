#include <ConnectivityAnalyerAdapter.hpp>
#include <RelationshipGraph.hpp>
#include <Friends.hpp>
#include <Relation.hpp>
#include <iostream>
#include <sstream>
#include <map>
#include <Graph.hpp>
#include <utils.h>

Graph* lib = new Graph();

ConnectivityAnalyerAdapter::ConnectivityAnalyerAdapter()
{
    this->libary = lib;
}


std::string ConnectivityAnalyerAdapter::Trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

std::pair<std::string, std::vector<std::string>> ConnectivityAnalyerAdapter::parseLine(std::string line)
{
    std::pair<std::string, std::vector<std::string>> result;
    size_t colonPos = line.find(':');
    
    if (colonPos != std::string::npos) {
        result.first = Trim(line.substr(0, colonPos));
        std::string rest = Trim(line.substr(colonPos + 1));
        
        std::istringstream iss(rest);
        std::string word;
        while (iss >> word) {
            result.second.push_back(word);
        }
    }
    
    return result;
}

std::vector<Relation*> ConnectivityAnalyerAdapter::parser(std::vector<std::string> scripts)
{
    std::vector<Relation*> graph = std::vector<Relation*>();

    for (auto line : scripts) {
        std::pair<std::string, std::vector<std::string>> result = parseLine(line);
        if (result.first.empty()) continue;

        Friends* friends = new Friends(result.second);
        Relation* relation = new Relation(result.first, friends);
        graph.push_back(relation);
    }
    
    return graph;
}


//TODO: Need to implement this method by thrid party library Graph
bool ConnectivityAnalyerAdapter::hasConnection(std::vector<Relation*> graph, const std::string& name1, const std::string& name2)
{
    std::vector<std::vector<std::string>> connections = ToConnections(graph);
    libary->SetConnections(connections);
    return this->libary->hasConnection(name1, name2);
}


std::vector<std::string> ConnectivityAnalyerAdapter::isMutualFriend(std::vector<Relation*> graph, std::string name1, std::string name2)
{
    std::vector<std::vector<std::string>> connections = ToConnections(graph);
    libary->SetConnections(connections);
    return this->libary->isMutualFriend(name1, name2);
}

std::vector<std::vector<std::string>> ConnectivityAnalyerAdapter::ToConnections(std::vector<Relation*> graph)
{
    std::vector<std::vector<std::string>> connections;

    for (auto relation : graph) {
        for (auto m: relation->GetRelations()) {
            connections.push_back({m.first});
            connections.back().insert(connections.back().end(), m.second->GetFriends().begin(), m.second->GetFriends().end());
        }
    }

    return connections;
}

ConnectivityAnalyerAdapter::~ConnectivityAnalyerAdapter()
{
}