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

    API api{api_key, link};
    api.startSession();



    Movement movement("3fa85f64-5717-4562-b3fc-2c963f66afa6", 15);
    std::vector<Movement> movements = { movement };

    api.playRound(0, movements);

    return 0;

    api.endSession();
    return 0;
    Engine engine;

    engine.run();

    return 0;
}
