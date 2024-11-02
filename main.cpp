#include <iostream>
#include <fstream>

#include "Engine.h"
#include "ResourceManager.h"
#include "API.h"
#include "CSVParser.h"

// #include <cpr/cpr.h>
#include <nlohmann/json.hpp>

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

    std::ifstream fin("resources/api_config.json");
    nlohmann::json api_json = nlohmann::json::parse(fin);

    API api{api_json["api_key"], api_json["api_link"]};

    CSVParser parser;


    return 0;
}
