#include "Rank.hpp"

std::map<Rank,std::string> rankToString =
{
    {Rank::Thr,"1"},
    {Rank::Four,"2"},
    {Rank::Five,"3"},
    {Rank::Six,"4"},
    {Rank::Seven,"5"},
    {Rank::Eight,"6"},
    {Rank::Night,"7"},
    {Rank::Ten,"8"},
    {Rank::J,"9"},
    {Rank::Q,"10"},
    {Rank::K,"11"},
    {Rank::A,"12"},
    {Rank::Sec,"13"},
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

std::map<std::string, Rank> charTorank = 
{
    {"A", Rank::A},
    {"2", Rank::Sec},
    {"3", Rank::Thr},
    {"4", Rank::Four},
    {"5", Rank::Five},
    {"6", Rank::Six},
    {"7", Rank::Seven},
    {"8", Rank::Eight},
    {"9", Rank::Night},
    {"10", Rank::Ten},
    {"J", Rank::J},
    {"Q", Rank::Q},
    {"K", Rank::K}
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

Rank CharToRank(std::string c)
{
    auto it = charTorank.find(c);
    if( it != charTorank.end())
        return it->second;
    
    return Rank::None;
}

int RankToNumber(Rank rank)
{
    return std::stoi(RankToString(rank));
}