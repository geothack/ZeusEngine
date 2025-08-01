#include "Zeus.h"


class Game : public ZApplication
{
public:
    Game()
    {
        ZApplication::Update(MainLevel);
    }

    ~Game()
    {

    }

    ZLevel MainLevel{};

};


ZApplication* CreateZApplication()
{
    return new Game();
}