#ifndef _TREASURE_H_
#define _TREASURE_H_

#include "Mapobject.hpp"
#include "Content.hpp"
#include <unordered_map>

class Coord;
class State;

class Treasure : public Mapobject
{
private:
    /* data */
    Content content;
public:
    Treasure(Coord* pos);
    ~Treasure();

    //TODO
    State* open();

    //method
    std::string NameOfContent();

    //getter
    Content GetContent();

    //setter
    void SetContent(Content content);

protected:
    std::unordered_map<Content, std::string> content2str = {
        {Content::SuperStar, "無敵星星"},
        {Content::Posion, "毒藥"},
        {Content::Accelerating, "加速藥水"},
        {Content::Healing, "補血罐"},
        {Content::Devil, "惡魔果實"},
        {Content::KingRock, "王者之印"},
        {Content::DokoDemoDoor, "任意門"}
    };
};


#endif /* _TREASURE_H_ */
