#include "Content.hpp"
#include <random>
#include <State.hpp>
#include <Poisoned.hpp>
#include <Invincible.hpp>
#include <Healing.hpp>
#include <Teleport.hpp>
#include <Erupting.hpp>
#include <Accelerated.hpp>
#include <Orderless.hpp>
#include <Stockpile.hpp>
#include <Role.hpp>


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
            return Content::Heal;
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

State* content2State(Role* role, Content content)
{
    switch (content) {
    case SuperStar:
        return new Invincible(role);
    case Posion:
        return new Poisoned(role);
    case Accelerating:
        return new Accelerated(role);
    case Heal:
        return new Healing(role);
    case Devil:
        return new Orderless(role);
    case KingRock:
        return new Stockpile(role);
    case DokoDemoDoor:
        return new Teleport(role);
    }
}