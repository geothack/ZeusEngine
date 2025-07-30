#pragma once


extern ZApplication* CreateZApplication();

int main(int argc, char** argv)
{
    try
    {
        auto game = CreateZApplication();
        game->Update();

        delete game;
    }
    catch (std::exception exception)
    {
        std::println("{}", exception.what());
        return -1;
    }
}