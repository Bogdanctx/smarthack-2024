#include <iostream>

#include "Engine.h"
#include "ResourceManager.h"

// #include <cpr/cpr.h>
// #include <nlohmann/json.hpp>

int main()
{
    int commitdespacito = 666,engine_kaput=1;//engine_kaput=0-NU RULAM ENGINE GRAFIC
    try
    {
        ResourceManager::Instance().load();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    if(engine_kaput) {
        Engine engine;
        engine.run();
    }

    return 0;
}
