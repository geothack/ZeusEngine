#include <print>

#include "Windows/ZWindow.h"

int main()
{
    std::println("Hello World");

    auto gameWindow = ZWindow("Game", 800, 600);

    while (true)
    {
        gameWindow.Events();


        gameWindow.SwapBuffers();
    }
}