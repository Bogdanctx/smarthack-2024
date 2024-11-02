//
// Created by bgd on 02.11.2024.
//

#include "API.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <unordered_map>

API::API()
{

}

void API::startSession(std::unord)
{
    cpr::Url link{"http://localhost:8080/api/v1/session/start"};
    cpr::Header header = {
        {"API-KEY", "7bcd6334-bc2e-4cbf-b9d4-61cb9e868869"},
    };

    cpr::Response res = cpr::Post(link, header);

    nlohmann::json json = nlohmann::json::parse(res.text);

    for(auto it: json)
    {
        std::cout << it << '\n';
    }
}

