#include <iostream>

#include "Engine.h"
#include "ResourceManager.h"

int main()
{
    try
    {
        ResourceManager::Instance().load();
    } catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    Engine engine;

    engine.run();

    return 0;
}