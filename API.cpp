//
// Created by bgd on 02.11.2024.
//

#include "API.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

void API::startSession(std::unordered_map<std::string, std::vector<std::string>> data)
{
    cpr::Url link{"http://localhost:8080/api/v1/session/start"};
    cpr::Header header = {
        {"API-KEY", "7bcd6334-bc2e-4cbf-b9d4-61cb9e868869"},
    };

    nlohmann::json json = {
        {""}
    };

    cpr::Response res = cpr::Post(link, header);
}


void API::playRound()
{
    nlohmann::json j;

    j["day"] = "12";
    j["movements"] = nlohmann::json::array();

    j["movements"].push_back({
        {"connectionId", "3fa85f64-5717-4562-b3fc-2c963f66afa6"},
        {"amount", "0"}
    });

    cpr::Response res = cpr::Post(
        cpr::Url{"http://localhost:8080/api/v1/play/round"},
        cpr::Header{
            {"API-KEY", "7bcd6334-bc2e-4cbf-b9d4-61cb9e868869"},
            {"SESSION-ID", "bf433055-79e1-437e-9ab9-378712326bc8"},
            {"Content-Type", "application/json"}
        },
        cpr::Body{j.dump()}
    );

    nlohmann::json parsed = nlohmann::json::parse(res.text);

    std::cout << res.status_code << '\n';

    for(auto d: parsed["demand"])
    {
        std::string customerId = d["customerId"].get<std::string>();
        unsigned long long amount = d["amount"].get<unsigned long long>();
        int postDay = d["postDay"].get<unsigned long long>();
        int startDay = d["startDay"].get<unsigned long long>();
        int endDay = d.at("endDay");

        std::cout << customerId << ' ' << amount << ' ' <<  postDay << ' ' << startDay << ' ' << endDay << ' ' << std::endl;
    }

}

