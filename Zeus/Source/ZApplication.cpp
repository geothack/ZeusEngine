#include "Core/CoreLibrary.h"
#include "ZApplication.h"

ZApplication::ZApplication()
{
}

ZApplication::~ZApplication()
{
}

void ZApplication::Update()
{
    std::println("Hello World");

    auto gameWindow = ZWindow("Game", 800, 600);

    while (true)
    {
        gameWindow.Events();


        gameWindow.SwapBuffers();
    }
}
