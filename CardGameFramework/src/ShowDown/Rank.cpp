#include "../include/ShowDown/Rank.hpp"

std::map<Rank,std::string> rankToString =
{
    {Rank::A,"1"},
    {Rank::Sec,"2"},
    {Rank::Thr,"3"},
    {Rank::Four,"4"},
    {Rank::Five,"5"},
    {Rank::Six,"6"},
    {Rank::Seven,"7"},
    {Rank::Eight,"8"},
    {Rank::Night,"9"},
    {Rank::Ten,"10"},
    {Rank::J,"11"},
    {Rank::Q,"12"},
    {Rank::K,"13"}
};

std::map<Rank,std::string> rankToName =
{
    {Rank::A,"A"},
    {Rank::Sec,"2"},
    {Rank::Thr,"3"},
    {Rank::Four,"4"},
    {Rank::Five,"5"},
    {Rank::Six,"6"},
    {Rank::Seven,"7"},
    {Rank::Eight,"8"},
    {Rank::Night,"9"},
    {Rank::Ten,"10"},
    {Rank::J,"J"},
    {Rank::Q,"Q"},
    {Rank::K,"K"}
};

std::string RankToString(Rank rank)
{
    auto it = rankToString.find(rank);
    if(it != rankToString.end())
    {
        return it->second;
    }
    return "0";
}

std::string RankToName(Rank rank)
{
    auto it = rankToName.find(rank);
    if(it != rankToString.end())
    {
        return it->second;
    }
    return "0";
}