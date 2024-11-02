#include "API.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

API::API(const std::string& key, const std::string& link) : key(key), link(link)
{}


void API::startSession()
{
    cpr::Response res = cpr::Post(
        cpr::Url{link + "/api/v1/session/start"},
        cpr::Header{
        	{"API-KEY", key},
        	{"Content-Type", "application/json"}
        }
    );

    session = res.text;

    std::cout << "Started session: key=" << key << "; session=" << session << std::endl;
}

void API::endSession()
{
    cpr::Response res = cpr::Post(
        cpr::Url{link + "/api/v1/session/end"},
        cpr::Header{
            {"API-KEY", key},
            {"Content-Type", "application/json"}
        }
    );
}

std::vector<Demand> API::playRound(int day, std::vector<Movement> movements)
{
    nlohmann::json j;

    j["day"] = std::to_string(day);
    j["movements"] = nlohmann::json::array();

    for(const Movement& movement : movements)
    {
        std::string connectionId = movement.connectionId;
        unsigned long long amount = movement.amount;

        j["movements"].push_back(
            {
                {"connectionId", connectionId},
            {   "amount", amount}
            }
        );
    }

    cpr::Response res = cpr::Post(
        cpr::Url{link + "/api/v1/play/round"},
        cpr::Header{
            {"API-KEY", key},
            {"SESSION-ID", session},
            {"Content-Type", "application/json"}
        },
        cpr::Body{j.dump()}
    );

    nlohmann::json parsed = nlohmann::json::parse(res.text);

    std::vector<Demand> demands;

    for(auto d: parsed["demand"])
    {
        std::string customerId = d["customerId"].get<std::string>();
        unsigned long long amount = d["amount"].get<unsigned long long>();
        unsigned int postDay = d["postDay"].get<unsigned int>();
        unsigned int startDay = d["startDay"].get<unsigned int>();
        unsigned int endDay = d.at("endDay");

        Demand new_demand(customerId, amount, postDay, startDay, endDay);
        demands.push_back(new_demand);

        std::cout << customerId << ' ' << amount << ' ' << postDay << ' ' << startDay << ' ' << endDay << std::endl;
    }

    return demands;
}

