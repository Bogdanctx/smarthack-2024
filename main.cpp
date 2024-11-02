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

    CSVParser parser;
    auto map = parser.getDemands();

    for(auto it: map)
    {
        std::cout << it.first << ' ';
        for(auto it2: it.second)
        {
            std::cout << it2 << ' ';
        }
        std::cout << '\n';
    }


    return 0;
}
