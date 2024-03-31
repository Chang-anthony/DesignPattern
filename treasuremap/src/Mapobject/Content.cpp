#include "Content.hpp"
#include <random>


Content randomContent()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 6); // 0 到 6的随机整数

    int randomValue = dis(gen);
    Content content;
    switch (randomValue) {
        case 0:
            return Content::SuperStar;
            break;
        case 1:
            return Content::Posion;
            break;
        case 2:
            return Content::Accelerating;
            break;
        case 3:
            return Content::Healing;
            break;
        case 4:
            return Content::Devil;
            break;
        case 5:
            return Content::KingRock;
            break;
        case 6:
            return Content::DokoDemoDoor;
            break;
        default:
            return randomContent();
            break;
    }
}