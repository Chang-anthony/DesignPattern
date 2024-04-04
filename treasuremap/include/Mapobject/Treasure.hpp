#ifndef _TREASURE_H_
#define _TREASURE_H_

#include "Mapobject.hpp"
#include "Content.hpp"
#include <unordered_map>

class Coord;
class State;
class Adventure;
class Role;

class Treasure : public Mapobject
{
private:
    /* data */
    Content content;
public:
    Treasure(Coord* pos, Adventure* game);
    ~Treasure();

    void move(int x, int y) override;

    void open(Role* role);
    static Treasure* genTreasure(Coord* newPos, Adventure* game);

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
        {Content::Heal, "補血罐"},
        {Content::Devil, "惡魔果實"},
        {Content::KingRock, "王者之印"},
        {Content::DokoDemoDoor, "任意門"}
    };
};


#endif /* _TREASURE_H_ */
