#include <Adventure.hpp>
#include <Round.hpp>
#include <Mapobject.hpp>
#include <Charator.hpp>
#include <Role.hpp>
#include <State.hpp>
#include <utils.h>
#include <Coord.hpp>

Round::Round(Adventure* game)
{
    this->game = utils::RequireNonNull(game);
}

void Round::gen()
{
    int count = 1;
    std::vector<std::string> targets = {"M", "X"};
    srand(time(nullptr));
    while (count > 0) {
        int randomNumber = rand() % targets.size();
        Mapobject* gens = Mapobject::GenObj(game, targets[randomNumber]);
            if(game->IsNullObj(gens->GetCoord())) {
                int x = gens->GetCoord()->GetX();
                int y = gens->GetCoord()->GetY();
                game->SetObj(gens);
                count--;
            }
    }
}

void Round::run()
{
    gen();

    //render
    Charator* charator = game->GetCharator();
    std::cout << "主角的生命: " << charator->GetHp() << " 狀態: " << charator->GetState()->StateName() << std::endl;
    std::cout << std::endl;
    render();

    //role action
    operation();
}

void Round::render()
{
    int boundx = game->GetBoundX();
    int boundy = game->GetBoundY();
    std::vector<std::vector<Mapobject*>> objs = game->GetObjs();

    for (int i = 0; i < boundx + 1; i++) {
        std::cout << "# ";
    }
    std::cout << "#" <<  std::endl;

    for (auto m : objs) {
        std::cout << "# ";
        for (auto obj : m) {
            if(obj)
                std::cout << obj->GetSymbol() << " ";
            else
                std::cout << ". ";
        }
        std::cout << "#" << std::endl;
    }
    
    for (int i = 0; i < boundx + 1; i++) {
        std::cout << "# ";
    }
    std::cout << "#" << std::endl;
}

void Round::operation()
{
    Charator* charator = game->GetCharator();
    charator->action();

    std::vector<std::vector<Mapobject*>> objs = game->GetObjs();

    for (auto m : objs) {
        for (auto obj : m) {
            if(obj && obj->GetSymbol() == "M") {
                Role* monster = (Role*) obj;
                monster->action();
            }
        }
    }
}

Round::~Round()
{
}