#include <ConnectivityAnalyerAdapter.hpp>
#include <RelationshipGraph.hpp>
#include <Friends.hpp>
#include <Relation.hpp>
#include <iostream>
#include <sstream>
#include <map>


ConnectivityAnalyerAdapter::ConnectivityAnalyerAdapter(/* args */)
{
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

RelationshipGraph* ConnectivityAnalyerAdapter::parser(std::vector<std::string> scripts)
{
    RelationshipGraph* graph = new RelationshipGraph();

    for (auto line : scripts) {
        std::pair<std::string, std::vector<std::string>> result = parseLine(line);
        if (result.first.empty()) continue;

        Friends* friends = new Friends(result.second);
        Relation* relation = new Relation(result.first, friends);
        graph->AddRelation(relation);
    }
    
    return graph;
}


ConnectivityAnalyerAdapter::~ConnectivityAnalyerAdapter()
{
}