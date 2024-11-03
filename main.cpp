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
    api.startSession();

    std::vector<Demand> demands;
    CSVParser parser;

    std::vector<Movement> movements;

    for(int i = 0; i <= 42; i++)
    {
        auto tanks = parser.getTanks();
        auto connections = parser.getConnections();

        for(Demand& d: demands)
        {
            if(d.startDay == i)
            {
                for(auto connection: connections)
                {
                    for(auto tank: tanks)
                    {
                        if(connection.second.from_id == tank.first && connection.second.to_id == d.customerId)
                        {
                            if(tank.second.cat_e_ocupat > d.amount)
                            {
                                tank.second.cat_e_ocupat -= d.amount;
                                d.terminat = true;

                                movements.push_back(Movement(connection.first, d.amount));
                            }
                        }
                    }
                }
            }
        }

        auto rafinarii = parser.getRefineries();

        for(auto rafinarie: rafinarii)
        {
            std::string id_rafinarie = rafinarie.second.name;
            int nr_tankuri = 0;
            for(auto connection: connections)
            {
                if(connection.second.from_id == id_rafinarie)
                {
                    unsigned long long productie = rafinarie.second.production;

                    for(auto tank: tanks)
                    {
                        std::string id_tank = tank.second.name;
                        if(connection.second.to_id == id_tank)
                        {
                            nr_tankuri++;
                        }
                    }
                }
            }

            for(auto connection: connections)
            {
                if(connection.second.from_id == id_rafinarie)
                {
                    bool has_break = false;
                    unsigned long long productie = rafinarie.second.production;

                    for(auto tank: tanks)
                    {
                        std::string id_tank = tank.second.name;
                        if(connection.second.to_id == id_tank)
                        {
                            tank.second.cat_e_ocupat += productie;
                            std::cout << tank.second.cat_e_ocupat << std::endl;
                            movements.push_back(Movement(connection.first, productie));
                            has_break = true;
                            break;
                        }
                    }
                    if(has_break)
                    {
                        break;
                    }
                }
            }
        }

        std::vector<Demand> new_demands = api.playRound(i, movements);

        for(Demand& d: new_demands)
        {
            demands.push_back(d);
        }
    }
    api.endSession();


    return 0;
}
