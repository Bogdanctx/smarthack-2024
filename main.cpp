#include <iostream>

#include "Engine.h"
#include "ResourceManager.h"
#include "CSVParser.h"
// #include <cpr/cpr.h>
// #include <nlohmann/json.hpp>

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

    //API api;
    //api.startSession();
    CSVParser csv;
    csv.getConnections();
    csv.getCustomers();
    csv.getDemands();
    csv.getRefineries();
    csv.getTanks();
    Engine engine;

    engine.run();

    return 0;
}
