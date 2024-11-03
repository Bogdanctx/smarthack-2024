#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Engine.h"
#include "ResourceManager.h"
#include "API.h"
#include "CSVParser.h"
#include "structs.h"
#include <nlohmann/json.hpp>

bool cmpRefs(const std::pair<std::string, Refinery>& a, const std::pair<std::string, Refinery>& b) {
    return (static_cast<double>(a.second.cat_e_ocupat) / a.second.capacity) > (static_cast<double>(b.second.cat_e_ocupat) / b.second.capacity);
}

bool cmpTanks(const std::pair<std::string, Tank>& a, const std::pair<std::string, Tank>& b) {
    return (static_cast<double>(a.second.cat_e_ocupat) / a.second.capacity) > (static_cast<double>(b.second.cat_e_ocupat) / b.second.capacity);
}


void processDemandsAndCalculateStress(std::vector<Demand>& total_demands, const std::vector<Demand>& api_new_demands, std::unordered_map<std::string, Tank>& tanks) {
    // Add new demands to the total demands list
    for (const Demand& demand : api_new_demands) {
        total_demands.push_back(demand);
    }

    // Calculate stress for each tank
    for (auto& [tank_id, tank] : tanks) {
        tank.stress = static_cast<double>(tank.cat_e_ocupat) / tank.capacity;
    }
}


void handleDemands(std::unordered_map<std::string, Demand>& demands, std::unordered_map<std::string, Tank>& tanks, const std::unordered_map<std::string, Connection>& connections, int currentDay) {
    for (auto it = demands.begin(); it != demands.end(); ) {
        Demand& demand = it->second;
        bool demandMet = false;

        // Find the main storage closest to the client
        std::string bestStorageId;
        double bestCost = std::numeric_limits<double>::max();
        for (const auto& [tankId, tank] : tanks) {
            if (connections.find(tankId) != connections.end() && connections.at(tankId).to_id == demand.customerId) {
                double dist = connections.find(tankId)->second.distance; ;
                if (dist < bestCost) {
                    bestCost = dist;
                    bestStorageId = tankId;
                }
            }
        }
        if (bestStorageId.empty()) {
            ++it;
            continue;
        }

        // Check penalties for each storage connected to the client
        for (const auto& [tankId, tank] : tanks) {
            if (connections.find(tankId) != connections.end() && connections.at(tankId).to_id == demand.customerId) {
                unsigned long long amountToTransfer = std::min(demand.amount, tank.cat_e_ocupat);
                unsigned long long leadTime = connections.at(tankId).lead_time_days;
                unsigned long long arrivalDay = currentDay + leadTime;

                if (arrivalDay > demand.endDay) {
                    // Too late, skip this demand
                    ++it;
                    continue;
                }

                if (arrivalDay < demand.startDay) {
                    // Too early, skip this storage
                    continue;
                }

                if (amountToTransfer > connections.at(tankId).max_capacity) {
                    // Exceeds road capacity, transfer as much as possible
                    amountToTransfer = connections.at(tankId).max_capacity;
                }

                if (tank.cat_e_ocupat - amountToTransfer < tank.underflow_penalty) {
                    // Underflow penalty, skip this storage
                    continue;
                }

                // Transfer the amount and update the storage
                tank.cat_e_ocupat -= amountToTransfer;
                std::cout << "Transferred " << amountToTransfer << " units from tank " << tankId << " to customer " << demand.customerId << std::endl;

                if (amountToTransfer == demand.amount) {
                    // Demand fully satisfied
                    it = demands.erase(it);
                    demandMet = true;
                    break;
                } else {
                    // Partially satisfied, update the demand
                    demand.amount -= amountToTransfer;
                }
            }
        }

        if (!demandMet) {
            ++it;
        }
    }
}


int main() {
    int engine_kaput = 1; // engine_kaput=0-NU RULAM ENGINE GRAFIC
    try {
        ResourceManager::Instance().load();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    std::ifstream fin("resources/api_config.json");
    nlohmann::json api_json = nlohmann::json::parse(fin);

    API api{api_json["api_key"], api_json["api_link"]};
    api.startSession();
    std::vector<Demand> api_new_demands = api.playRound(0, {});
    std::vector<Demand> total_demands;
    CSVParser parser;

    auto refs = parser.getRefineries();
    auto tanks = parser.getTanks();
    auto connections = parser.getConnections();
    auto customers = parser.getCustomers();
    auto demands = parser.getDemands();

    std::vector<std::pair<std::string, Refinery>> ref_vector;
    std::vector<std::pair<std::string, Tank>> tank_vector;

    for (int i = 1; i <= 42; i++) {
        api_new_demands = api.playRound(i, {});
        // Update refinery storage
        for (auto& [id, refinery] : refs) {
            refinery.cat_e_ocupat += refinery.max_output;
            ref_vector.emplace_back(id, refinery);
        }

        // Sort refineries and tanks
        std::sort(ref_vector.begin(), ref_vector.end(), cmpRefs);
        std::sort(tank_vector.begin(), tank_vector.end(), cmpTanks);

        // Process demands and calculate stress per storage tank
        processDemandsAndCalculateStress(total_demands, api_new_demands, tanks);


        // Distribute fuel from refineries to tanks
        for (auto& [ref_id, refinery] : ref_vector) {
            double total_stress = 0;
            for (auto& [tank_id, tank] : tank_vector) {
                total_stress += tank.stress;
            }

            for (auto& [tank_id, tank] : tank_vector) {
                double fuel_to_transfer = (tank.stress / total_stress) * refinery.max_output;
                if (fuel_to_transfer > (tank.capacity - tank.cat_e_ocupat)) {
                    fuel_to_transfer = tank.capacity - tank.cat_e_ocupat;
                }
                tank.cat_e_ocupat += fuel_to_transfer;
                refinery.cat_e_ocupat -= fuel_to_transfer;
            }

            // Handle overflow
            if (refinery.cat_e_ocupat > refinery.capacity) {
                // Implement overflow handling logic here
            }
        }

        // Sort demands
        std::sort(total_demands.begin(), total_demands.end(), [](const Demand& a, const Demand& b) {
            return (a.endDay - a.startDay) < (b.endDay - b.startDay);
        });

        // Calculate the number of demands to prioritize (first 5%)
        size_t prioritize_count = static_cast<size_t>(total_demands.size() * 0.05);

        // Sort the first 5% by the closest expected delivery day considering lead time
        std::partial_sort(total_demands.begin(), total_demands.begin() + prioritize_count, total_demands.end(), [&](const Demand& a, const Demand& b) {
            unsigned long long a_lead_time = connections[a.customerId].lead_time_days;
            unsigned long long b_lead_time = connections[b.customerId].lead_time_days;
            return (a.endDay - a_lead_time) < (b.endDay - b_lead_time);
        });

        // Sort the remaining 95% by the fraction amount / (expected day - lead time)
        std::sort(total_demands.begin() + prioritize_count, total_demands.end(), [&](const Demand& a, const Demand& b) {
            unsigned long long a_lead_time = connections[a.customerId].lead_time_days;
            unsigned long long b_lead_time = connections[b.customerId].lead_time_days;
            double a_fraction = static_cast<double>(a.amount) / (a.endDay - a_lead_time);
            double b_fraction = static_cast<double>(b.amount) / (b.endDay - b_lead_time);
            return a_fraction > b_fraction;
        });

        // Fulfill demands
        handleDemands(demands, tanks, connections, i);

    }
/*
    if (engine_kaput) {
        Engine engine;
        engine.run();
    }
*/
    return 0;
}