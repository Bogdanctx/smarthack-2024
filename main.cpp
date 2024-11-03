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
    auto tanks = parser.getTanks();
    auto connections = parser.getConnections();
    auto refineries = parser.getRefineries();

    for (int day = 0; day <= 42; day++) {
        for (Demand& d : demands) {
            if (d.terminat) continue;

            for (const auto& connection : connections) {
                auto from_tank_it = tanks.find(connection.second.from_id);
                if (from_tank_it != tanks.end() && connection.second.to_id == d.customerId) {
                    Tank& from_tank = from_tank_it->second;

                    if (from_tank.initial_stock >= d.amount) {
                        movements.emplace_back(connection.first, d.amount);
                        from_tank.initial_stock -= d.amount;
                        d.terminat = true;
                        break;  // Demand fulfilled; no need to check further connections
                    }
                }
            }
        }

        // Sort tanks by initial stock for efficient refilling
        std::vector<std::reference_wrapper<Tank>> tanks_sorted;
        for (auto& tank_pair : tanks) {
            tanks_sorted.push_back(tank_pair.second);
        }

        std::sort(tanks_sorted.begin(), tanks_sorted.end(), [](const Tank& a, const Tank& b) {
            return a.initial_stock < b.initial_stock;
        });

        // Process refineries and refill tanks
        for (const auto& refinery : refineries) {
            for (const auto& connection : connections) {
                if (connection.second.from_id == refinery.second.id) {
                    for (Tank& tank : tanks_sorted) {
                        if (connection.second.to_id == tank.id) {
                            unsigned long long transfer_amount = std::min(refinery.second.max_output, refinery.second.production);
                            tank.initial_stock += transfer_amount;
                            movements.emplace_back(connection.first, transfer_amount);
                            break;  // Move to the next connection once a tank is refilled
                        }
                    }
                }
            }
        }

        // Update demands based on new round data
        auto new_demands = api.playRound(day, movements);
        demands.insert(demands.end(), new_demands.begin(), new_demands.end());
}

    api.endSession();


    return 0;
}
