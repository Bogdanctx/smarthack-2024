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
    int commitdespacito = 666,engine_kaput=1;//engine_kaput=0-NU RULAM ENGINE GRAFIC
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


    std::vector<Demand> api_new_demands = api.playRound(0, {});
    std::vector<Demand> total_demands;

    for(const Demand& demand: api_new_demands)
    {
        total_demands.push_back(demand);
    }
    if(engine_kaput) {
        Engine engine;
        engine.run();
    }


    return 0;
}
