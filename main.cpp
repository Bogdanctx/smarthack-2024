#include <iostream>
#include <fstream>
#include "Engine.h"
#include "ResourceManager.h"
#include "CSVParser.h"
// #include <cpr/cpr.h>
// #include <nlohmann/json.hpp>

#include <chrono>

#include "API.h"

int main()
{
    try
    {
        ResourceManager::Instance().load();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    std::ifstream fin("resources/link.txt");
    std::string link, api_key;

    fin >> link >> api_key;

    API api{link, api_key};
    api.startSession();


    return 0;
    Engine engine;

    engine.run();

    return 0;
}
