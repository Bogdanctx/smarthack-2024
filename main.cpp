#include <iostream>
#include <fstream>
#include "Engine.h"
#include "ResourceManager.h"
#include "API.h"
#include "CSVParser.h"
// #include <cpr/cpr.h>
#include <queue>
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
    api.startSession();

    std::vector<Demand> demands;
    CSVParser parser;

    std::vector<Movement> movements;

    for(int day = 0; day <= 42; day++)
    {
        auto tanks = parser.getTanks();
        auto connections = parser.getConnections();

        for(Demand& d: demands)
        {
            if(d.terminat)
            {
                continue;
            }

            for(auto& connection: connections)
            {
                for(auto& tank: tanks)
                {
                    if(tank.first == connection.second.from_id && connection.second.to_id == d.customerId)
                    {
                        if(tanks[connection.second.from_id].initial_stock >= d.amount)
                        {
                            movements.push_back(Movement{connection.first, d.amount});
                            tanks[connection.second.from_id].initial_stock -= d.amount;
                            d.terminat = true;
                        }
                    }
                }
            }
        }

        std::vector<Tank> tanks2;
        for(auto& tank: tanks)
        {
            tanks2.push_back(tank.second);
        }

        std::sort(tanks2.begin(), tanks2.end(), [](const Tank& tank1, const Tank& tank2)
        {
            return tank1.initial_stock < tank2.initial_stock;
        });

        auto rafinarii = parser.getRefineries();
        for(auto& rafinarie: rafinarii)
        {
            for(auto& connection: connections)
            {
                if(connection.second.from_id == rafinarie.second.id)
                {
                    for(auto& tank: tanks2)
                    {
                        if(connection.second.to_id == tank.id)
                        {
                            unsigned long long a = std::min(rafinarie.second.max_output, rafinarie.second.production);
                            tank.initial_stock += a;
                            movements.push_back(Movement(connection.first, a));
                        }
                    }
                }
            }
        }

        for(auto& tank: tanks2)
        {
            tanks[tank.id] = tank;
        }

        std::vector<Demand> new_demands = api.playRound(day, movements);
        for(auto& new_demand: new_demands)
        {
            demands.push_back(new_demand);
        }

    }
    api.endSession();


    return 0;
}
