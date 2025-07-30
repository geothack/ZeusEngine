#include "Zeus.h"


class Game : public ZApplication
{
public:
    Game()
    {

    }

    ~Game()
    {

    }


};


ZApplication* CreateZApplication()
{
    return new Game();
}