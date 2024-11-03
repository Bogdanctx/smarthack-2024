#include <iostream>
#include <fstream>
#include "Engine.h"
#include "ResourceManager.h"
#include "API.h"
#include "CSVParser.h"
// #include <cpr/cpr.h>
#include <queue>
#include <nlohmann/json.hpp>
#include <vector>
#include <unordered_map>

struct ScheduledOperation {
    int day;         // Day when operation should be applied
    std::string tank_id;     // Target tank ID
    int amount;      // Amount to add (positive) or subtract (negative)
    ScheduledOperation(int day, const std::string &tank_id, int amount)
        : day(day),
          tank_id(tank_id),
          amount(amount) {
    }
};

int main() {
    int commitdespacito = 666, engine_kaput = 1; // engine_kaput=0-NU RULAM ENGINE GRAFIC
    try {
        ResourceManager::Instance().load();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::ifstream fin("resources/api_config.json");
    nlohmann::json api_json = nlohmann::json::parse(fin);

    API api{api_json["api_key"], api_json["api_link"]};
    api.startSession();

    std::vector<Demand> demands;
    CSVParser parser;
    std::vector<Movement> movements;
    std::vector<std::vector<std::pair<std::string, int>>> operatii(43);  // Track operations for 43 days
    std::vector<std::vector<ScheduledOperation>> scheduled_operations(43); // Pending operations with lead times
    auto tanks = parser.getTanks();
    auto connections = parser.getConnections();
    auto refineries = parser.getRefineries();

    for (int day = 0; day <= 42; day++) {
        // Process pending operations scheduled for today
        for (const auto& op : scheduled_operations[day]) {
            auto tank_it = tanks.find(op.tank_id);
            if (tank_it != tanks.end()) {
                tank_it->second.initial_stock += op.amount; // Apply scheduled addition/subtraction
                operatii[day].emplace_back(op.tank_id, op.amount); // Record operation
            }
        }

        // Handle demands
        for (Demand& d : demands) {
            if (d.terminat) continue;

            for (const auto& connection : connections) {
                auto from_tank_it = tanks.find(connection.second.from_id);
                if (from_tank_it != tanks.end() && connection.second.to_id == d.customerId) {
                    Tank& from_tank = from_tank_it->second;

                    if (from_tank.initial_stock >= d.amount) {
                        from_tank.initial_stock -= d.amount; // Immediate stock reduction
                        movements.emplace_back(connection.first, d.amount);

                        // Schedule the subtraction for future day considering lead time
                        int future_day = day + connection.second.lead_time_days;
                        if (future_day <= 42) {
                            scheduled_operations[future_day].push_back(ScheduledOperation(future_day, from_tank_it->first, -d.amount));
                        }

                        operatii[day].emplace_back(from_tank_it->first, -d.amount); // Record immediate change
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

                            // Schedule the addition based on lead time
                            int future_day = day + connection.second.lead_time_days;
                            if (future_day <= 42) {
                                scheduled_operations[future_day].push_back({future_day, tank.id, transfer_amount});
                            }

                            movements.emplace_back(connection.first, transfer_amount);
                            operatii[day].emplace_back(tank.id, transfer_amount); // Record immediate scheduling
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

    // Optional: Print operations recorded in operatii for verification
    for (int day = 0; day <= 42; ++day) {
        std::cout << "Day " << day << " operations:\n";
        for (const auto& op : operatii[day]) {
            int tank_id = op.first;
            int amount = op.second;
            std::cout << "  Tank " << tank_id << (amount > 0 ? " added " : " subtracted ") << abs(amount) << "\n";
        }
    }

    return 0;
}
