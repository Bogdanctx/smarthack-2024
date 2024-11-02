#include <iostream>
#include <fstream>
#include "Engine.h"
#include "ResourceManager.h"
#include "API.h"
#include "CSVParser.h"
// #include <cpr/cpr.h>
#include <nlohmann/json.hpp>

bool cmpRefs(const std::pair<std::string, Refinery>& a, const std::pair<std::string, Refinery>& b)
{
    return (static_cast<double>(a.second.cat_e_ocupat)/a.second.capacity)>(static_cast<double>(b.second.cat_e_ocupat)/b.second.capacity);
}

bool cmpTanks(const std::pair<std::string, Tank>& a, const std::pair<std::string, Tank>& b)
{
    return (static_cast<double>(a.second.cat_e_ocupat)/a.second.capacity)>(static_cast<double>(b.second.cat_e_ocupat)/b.second.capacity);
}

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

    std::vector<Demand> api_new_demands = api.playRound(0, {});
    std::vector<Demand> total_demands;
    CSVParser parser;

    auto refs = parser.getRefineries();
    auto tanks = parser.getTanks();
    auto connections = parser.getConnections();
    auto customers = parser.getCustomers();

    std::vector<std::pair<std::string, Refinery>> ref_vector;
    std::vector<std::pair<std::string, Tank>> tank_vector;

    for(int i=1;i<=42;i++)
    {
        for(auto& [id, refinery]: refs)
        {
            ref_vector.emplace_back(id, refinery);
            refinery.cat_e_ocupat += refinery.max_output;
        }
        for(auto& [id, tank]: tanks)
            tank_vector.emplace_back(id, tank);
        std::sort(ref_vector.begin(), ref_vector.end(), cmpRefs);
        std::sort(tank_vector.begin(), tank_vector.end(), cmpTanks);
    }

    for(const Demand& demand: api_new_demands)
    {
        total_demands.push_back(demand);
    }

    return 0;
}
