#ifndef _CONNECTIVITYANALYERADAPTER_H_
#define _CONNECTIVITYANALYERADAPTER_H_

#include <iostream>
#include <vector>
#include <RelationshipAnalyer.hpp>

class RelationshipGraph;

class ConnectivityAnalyerAdapter : public RelationshipAnalyer
{
private:
    /* data */
public:
    ConnectivityAnalyerAdapter(/* args */);
    ~ConnectivityAnalyerAdapter();

    //TODO: implement this method
    RelationshipGraph* parser(std::vector<std::string> scripts) override;
    bool hasConnection(const std::string& name1, const std::string& name2) override;
    std::vector<std::string> isMutualFriend(std::string name1, std::string name2) override;

protected:
    std::string Trim(const std::string& str);
    std::pair<std::string, std::vector<std::string>> parseLine(std::string line);
};


#endif /* _CONNECTIVITYANALYERADAPTER_H_ */
