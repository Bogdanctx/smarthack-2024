#include <iostream>

#include "Engine.h"
#include "ResourceManager.h"
#include "CSVParser.h"
// #include <cpr/cpr.h>
// #include <nlohmann/json.hpp>

#include "API.h"

int main()
{
    int commitdespacito = 666;
    try
    {
        ResourceManager::Instance().load();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    API api;
    api.startSession();

    Engine engine;

    engine.run();

    return 0;
}
